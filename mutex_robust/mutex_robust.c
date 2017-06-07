#include "trace.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/shm.h>

#define SHM_KEY 1000

int main()
{
    int ret = 0;
    int shm_id = shmget(SHM_KEY, sizeof(pthread_mutex_t), IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id < 0) {
        if (EEXIST == errno) {
            shm_id = shmget(SHM_KEY, 0, 0);
            if (shm_id < 0) {
                ETRACE("shmget() failed: shm_key[%d]", SHM_KEY);
                return -1;
            }

            ret = shmctl(shm_id, IPC_RMID, NULL);
            if (ret != 0) {
                ETRACE("shmctl() faile: shm_id[%d], errno[%d]", shm_id, errno);
                return -1;
            }

            shm_id = shmget(SHM_KEY, sizeof(pthread_mutex_t), IPC_CREAT | IPC_EXCL | 0666);
            if (shm_id < 0) {
                ETRACE("shmget() failed: errno[%d]", errno);
                return -1;
            }
        }
        else {
            ETRACE("shmget() failed: errno[%d]", errno);
            return -1;
        }
    }

    pthread_mutex_t *mutex = (pthread_mutex_t *)shmat(shm_id, NULL, 0);
    if ((void *)-1 == mutex) {
        ETRACE("shmat() failed: errno[%d]", errno);
        return -1;
    }

    pthread_mutexattr_t mutexattr;

    ret = pthread_mutexattr_init(&mutexattr);
    if (ret != 0) {
        ETRACE("pthread_mutexattr_init() failed: errno[%d]", errno);
        return -1;
    }

    ret = pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
    if (ret != 0) {
        ETRACE("pthread_mutexattr_setpshared() failed: errno[%d]", errno);
        return -1;
    }

    ret = pthread_mutexattr_setrobust(&mutexattr, PTHREAD_MUTEX_ROBUST);
    if (ret != 0) {
        ETRACE("pthread_mutexattr_setrobust() failed: errno[%d]", errno);
        return -1;
    }

    ret = pthread_mutex_init(mutex, &mutexattr);
    if (ret != 0) {
        ETRACE("pthread_mutex_init() failed: errno[%d]", errno);
        return -1;
    }

    ret = pthread_mutex_lock(mutex);
    if (ret != 0) {
        ETRACE("pthread_mutex_lock() failed: errno[%d]", errno);
        return -1;
    }

    int i = 0;
    while (i < 5) {
       if (0 == fork()) {
           pthread_mutex_t *mutex = (pthread_mutex_t *)shmat(shm_id, NULL, 0);
           if ((void *)-1 == mutex) {
               ETRACE("shmat() failed: errno[%d]", errno);
               return -1;
           }

           ret = pthread_mutex_lock(mutex);
           if (ret != 0) {
               if (EOWNERDEAD == ret) {
                   WTRACE("pthread_mutex_lock() succeed as owner dead, pid[%d]",
                          getpid());
                   ret = pthread_mutex_consistent(mutex);
                   if (ret != 0) {
                       ETRACE("pthread_mutex_consistent() failed: errno[%d]",
                              errno);
                       return -1;
                   }
               }
               else {
                   ETRACE("pthread_mutex_lock() failed: errno[%d]", errno);
                   return -1;
               }
           }

           sleep(5);
           return 0;
       }

       i++;
    }

    return 0;
}
