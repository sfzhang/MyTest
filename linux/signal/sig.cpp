#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int i = 0;

void handler(int signo)
{
    printf("i[%d], signal[%d]\n", i, signo);
    i++;
}

void wait_child()
{
    pid_t pid = fork();

    if (-1 == pid) {
        printf("fork() failed: errno[%d]", errno);
        return;
    }
    else if (0 == pid) {
        sleep(100);
        return;
    }
    else {
        printf("create child process success, pid[%ld]\n", pid);

        int status = 0;
        while (1) {
            pid_t ret = wait(&status);
            if (-1 == ret) {
                if (EINTR == errno) {
                    continue;
                }
                else {
                    printf("wait() failed: errno[%d]\n", errno);
                }
            }
            else {
                printf("wait() success: pid[%ld]\n", ret);
            }
        }
    }
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = handler;
    sa.sa_flags |= SA_RESTART;

    sigaction(SIGINT, &sa, NULL);

    wait_child();

    /*
    while (1) {
        int ret = sleep(100);
        printf("interrupt: ret[%d], errno[%d]\n", ret, errno);
    }
    */

    return 0;
}
