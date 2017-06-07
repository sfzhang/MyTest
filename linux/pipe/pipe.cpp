#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL) != 0) {
        printf("sigaction() ignore SIGPIPE failed: errno[%d]", errno);
    }

    int fd[2] = {0};

    if (pipe(fd) != 0) {
        printf("pipe() failed: errno[%d]\n", errno);
        return -1;
    }
    printf("pipe() success: fd { %d %d }\n", fd[0], fd[1]);

    close(fd[0]);

    if (write(fd[1], "abcdefg", 7) != 7) {
        printf("write() failed: errno[%d]\n", errno);
        return -1;
    }
    printf("write() success");

    return 0;
}
