#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define SHM_FILE "/tmp_pshm"
#define SHM_SIZE 128
#define SHM_MODE 0666

int main()
{
    int fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, SHM_MODE);
    if (fd < 0) {
        printf("shm_open() failed: errno[%d]", errno);
        return -1;
    }

    struct stat st = {0};
    if (fstat(fd, &st) < 0) {
        printf("fstat() failed: errno[%d]", errno);
        return -1;
    }

    printf("mode[%o], uid[%d], gid[%d], size[%lu]\n",
           st.st_mode, st.st_uid, st.st_gid, st.st_size);

    if (ftruncate(fd, 256) < 0) {
        printf("ftruncate() failed: errno[%d]", errno);
        return -1;
    }

    /* child */
    if (0 == fork()) {
        sleep(10);
        void *ptr = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (!ptr) {
            printf("mmap() failed: errno[%d]", errno);
            return -1;
        }
        printf("child ptr[%p]: %s\n", ptr, (char *)ptr);
        return 0;
    }
    else {
        void *ptr = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (!ptr) {
            printf("mmap() failed: errno[%d]", errno);
            return -1;
        }
        snprintf(ptr, 256, "Hello, POSIX shared memmory");

        printf("parent ptr[%p]: %s\n", ptr, (char *)ptr);

        /*
        if (shm_unlink(SHM_FILE) < 0) {
            printf("shm_unlink() failed: errno[%d]", errno);
            return -1;
        }
        */
        return 0;
    }
}
