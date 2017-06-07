#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define SHM_KEY  12321
#define SHM_SIZE 128
#define SHM_MODE 0666

int main()
{
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | SHM_MODE);
    if (shmid < 0) {
        printf("shmget() failed: errno[%d]", errno);
        return -1;
    }

    struct shmid_ds buf = {0};
    if (shmctl(shmid, IPC_STAT, &buf) < 0) {
        printf("shmctl() failed: errno[%d]", errno);
        return -1;
    }

    printf("segsz[%lu], lpid[%ld], cpid[%ld], nattch[%ld]\n",
           buf.shm_segsz, buf.shm_lpid, buf.shm_cpid, buf.shm_nattch);

    /* child */
    if (0 == fork()) {
        void *ptr = shmat(shmid, NULL, 0);
        if ((void *)-1 == ptr) {
            printf("shmat() failed: errno[%d]", errno);
            return -1;
        }

        void *ptr_2 = shmat(shmid, NULL, 0);
        if ((void *)-1 == ptr_2) {
            printf("shmat() failed: errno[%d]", errno);
            return -1;
        }

        if (ptr != ptr_2) {
            printf("ptr[%p], ptr_2[%p]\n", ptr, ptr_2);
            return -1;
        }

        sleep(10);
        printf("child ptr[%p]: %s\n", ptr, (char *)ptr);
        return 0;
    }
    else {
        void *ptr = shmat(shmid, NULL, 0);
        if ((void *)-1 == ptr) {
            printf("shmat() failed: errno[%d]", errno);
            return -1;
        }
        snprintf(ptr, 256, "Hello, POSIX shared memmory");

        printf("parent ptr[%p]: %s\n", ptr, (char *)ptr);

        sleep(5);
        if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            printf("shmctl() failed: errno[%d]", errno);
            return -1;
        }
        return 0;
    }
}
