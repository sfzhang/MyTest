#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <pthread.h>
#include <fcntl.h>
#include "trace.h"

int g_fd = -1;

void *thread_runner(void *arg)
{
    sleep(10);
    //close(g_fd);
    shutdown(g_fd, SHUT_WR);
    printf("g_fd is closed");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        ETRACE("usage: %s ip port", argv[0]);
        return -1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        ETRACE("socket() failed: errno[%d]", errno);
        return -1;
    }

    int flags = fcntl(sock_fd, F_GETFD);
    fcntl(sock_fd, F_SETFD, (flags | O_NONBLOCK));

    g_fd = sock_fd;

    struct sockaddr_in serv_address;
    bzero(&serv_address, sizeof(serv_address));
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, ip, &serv_address.sin_addr);
    serv_address.sin_port = htons(port);

    /* Connect */
    int ret = connect(sock_fd, (struct sockaddr *)&serv_address,
                      sizeof(serv_address));
    if (ret != 0) {
        ETRACE("connect() failed: errno[%d]", errno);
        return -1;
    }

    pthread_t t;
    pthread_create(&t, NULL, thread_runner, NULL);

    struct pollfd fds[1];
    fds[0].fd = sock_fd;
    fds[0].events = POLLOUT;

    //shutdown(sock_fd, SHUT_WR);
    //close(sock_fd);
    while (1) {
        int ret = poll(fds, 1, -1);
        if (ret < 0) {
            ETRACE("poll() failed: errno[%d]", errno);
            return -1;
        }
        else if (ret > 0) {
            if (fds[0].revents & (~POLLOUT)) {
                WTRACE("poll() success: revents[%#x]", fds[0].revents);
                return -1;
            }
        }
        else {
            ETRACE("timeout");
            return -1;
        }
    }

    return 0;
}
