#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    int fd[2] = {-1, -1};

    int ret = pipe2(fd, O_NONBLOCK);
    if (ret < 0) {
        printf("pipe2() failed: errno[%d]\n", errno);
        return -1;
    }

    char buf[1024] = {0};

    ssize_t size = read(fd[0], buf, 1024);
    if (size < 0) {
        printf("read() failed: errno[%d]\n", errno);
        return -1;
    }
    else {
        printf("read() success: ret[%d]\n", ret);
    }

    return 0;
}
