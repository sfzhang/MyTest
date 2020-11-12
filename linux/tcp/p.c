#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>

struct pollfd   fdList[1];

void *thread_runner(void *arg)
{
    sleep(5);
    close(fdList[0].fd);
    //shutdown(fdList[0].fd, SHUT_WR);
    //shutdown(fdList[0].fd, SHUT_RD);
    //shutdown(fdList[0].fd, SHUT_RDWR);
    printf("socket closed\n");
    pthread_exit(NULL);
}

int main(void)
{
    signal(SIGPIPE, SIG_IGN);
    struct  sockaddr_in hostAddr;
    int sockFD;
    char buf[32];
    pthread_t handle;

    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sockFD,F_SETFL,O_NONBLOCK|fcntl(sockFD,F_GETFL,0));

    inet_aton("127.0.0.1",&(hostAddr.sin_addr));
    hostAddr.sin_family = AF_INET;
    hostAddr.sin_port  = htons(12345);
    connect(sockFD,(struct sockaddr *)&hostAddr,sizeof(struct sockaddr));

    fdList[0].fd = sockFD;
    fdList[0].events = POLLOUT;

    pthread_create(&handle,NULL,thread_runner,NULL);

    while(1) {
        if(poll(fdList,1,-1) < 1) {
            printf("poll() failed");
            continue;
        }
        if(fdList[0].revents & POLLNVAL ) {
            printf("POLLNVAL\n");
            sleep(2);
            exit(-1);
        }
        if(fdList[0].revents & POLLOUT) {
            printf("connected\n");
            /*
            char a;
            int ret = write(sockFD, &a, 1);
            if (ret <= 0) {
                printf("write() failed: ret[%d], errno[%d]\n", ret, errno);
                return -1;
            }
            */
            fdList[0].events = POLLIN;
        }

        if(fdList[0].revents & POLLRDHUP ) {
            printf("POLLRDHUP\n");
            close(fdList[0].fd);
            exit(-1);
        }

        if(fdList[0].revents & POLLHUP ) {
            printf("POLLHUP\n");
            close(fdList[0].fd);
            exit(-1);
        }
        if(fdList[0].revents & (POLLIN | POLLPRI)) {
            printf("revents[%#x]", fdList[0].revents);
            if( read(fdList[0].fd, buf, sizeof(buf)) <= 0) {
                printf("read 0 \n");
                close(fdList[0].fd);
                exit(-1);
            }
        }
    }
    return 0;
}
