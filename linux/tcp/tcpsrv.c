#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "trace.h"

int process(int fd)
{
    char buffer[1024] = {0};
    ssize_t size = 0;
    while (1) {
        size = read(fd, buffer, sizeof(buffer));
        if (size < 0) {
            ETRACE("read() failed: errno[%d]", errno);
            return -1;
        }
        else if (0 == size) {
            WTRACE("read() failed as close by peer!");
            return 0;
        }

        ITRACE("read() success: buffer[%s]", buffer);
        memset(buffer, 0, sizeof(buffer));

        sleep(1);
        //close(fd);
        shutdown(fd, SHUT_RDWR);

        /*
        size = 1024;
        if (write(fd, buffer, size) != size) {
            ETRACE("write() failed: errno[%d]", errno);
            return -1;
        }

        sleep(3);
        */
    }

    return 0;
}

int main(int argc, char *argv[])
{
    signal(SIGCHLD, SIG_IGN);

    if (argc != 2) {
        ETRACE("usage: %s port", argv[0]);
        return -1;
    }

    int port = atoi(argv[1]);

    int serv_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock_fd < 0) {
        ETRACE("socket() failed: errno[%d]", errno);
        return -1;
    }

    int reuse_address = 1;
    int ret = setsockopt(serv_sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_address,
                         sizeof(reuse_address));
    if (ret < 0) {
        ETRACE("setsockopt() failed: level[SOL_SOCKET], optname[SO_REUSEADDR], "
               "optval[1], errno[%d]", errno);
        return -1;
    }

    struct sockaddr_in serv_address;
    bzero(&serv_address, sizeof(serv_address));
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_address.sin_port = htons(port);
    ret = bind(serv_sock_fd, (struct sockaddr *)&serv_address,
               sizeof(serv_address));
    if (ret != 0) {
        ETRACE("bind() failed: address[INADDR_ANY], port[%d], errno[%d]",
               port, errno);
        return -1;
    }

    if ((ret = listen(serv_sock_fd, 5)) != 0) {
        ETRACE("listen() failed: errno[%d]", errno);
        return -1;
    }

    /* Accept */
    struct sockaddr_in client_address;
    memset(&client_address, 0, sizeof(client_address));
    socklen_t address_length = sizeof(client_address);
    pid_t pid = -1; 
    int recv_sock_fd = -1; 
    while (1) {
        if ((recv_sock_fd = accept(serv_sock_fd, (struct sockaddr *)&client_address, &address_length)) < 0) {
            ETRACE("accept() failed: serv_sock_fd[%d], errno[%d]", serv_sock_fd, errno);
            break;
        }

        /* Create child process */
        if ((pid = fork()) < 0) {
            ETRACE("fork() failed: errno[%d]", errno);
            close(recv_sock_fd);
            break;
        }
        else if (0 == pid) { /* Child */
            close(serv_sock_fd);
            serv_sock_fd = -1; 

            /* Process */
            process(recv_sock_fd);

            /* break to exit */
            break;
        }

        close(recv_sock_fd);
        recv_sock_fd = -1;
    }

    return 0;
}
