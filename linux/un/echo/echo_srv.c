#include "trace.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAX_LINE 1024

int echo(int sock_fd)
{
    char buffer[MAX_LINE] = {0};

    int length = read(sock_fd, buffer, sizeof(buffer));
    if (length < 0) {
        ETRACE("read() failed: errno[%d]", errno);
        return -1;
    }

    DTRACE("read() success: buffer[%s], length[%d]", buffer, length);

    if (write(sock_fd, buffer, length) != length) {
        ETRACE("write() failed: errno[%d]", errno);
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf ("usage: %s pathname\n", argv[0]);
        return -1;
    }

    int serv_fd = -1;
    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serv_fd < 0) {
        ETRACE("socket() failed: errno[%d]", errno);
        return -1;
    }

    if ((unlink(argv[1]) != 0) && (errno != ENOENT)) {
        ETRACE("unlink() failed: file[%s], errno[%s]", argv[1], errno);
        return -1;
    }

    struct sockaddr_un addr_serv;
    bzero(&addr_serv, sizeof(addr_serv));
    addr_serv.sun_family = AF_UNIX;
    snprintf(addr_serv.sun_path, sizeof(addr_serv.sun_path), "%s", argv[1]);

    int ret = bind(serv_fd, (struct sockaddr *)&addr_serv, SUN_LEN(&addr_serv));
    if (ret != 0) {
        ETRACE("bind() failed: errno[%d]", errno);
        return -1;
    }

    ret = listen(serv_fd, 10);
    if (ret != 0) {
        ETRACE("listen() failed: errno[%d]", errno);
        return -1;
    }

    struct sockaddr_un addr_clt;
    socklen_t length = 0;
    while (1) {
        bzero(&addr_clt, sizeof(&addr_clt));
        length = sizeof(addr_clt);
        int sock_fd = accept(serv_fd, (struct sockaddr *)&addr_clt, &length);
        if (sock_fd < 0) {
            ETRACE("accept() failed: errno[%d]", errno);
            return -1;
        }

        DTRACE("%s", addr_clt.sun_path);

        if (echo(sock_fd) != 0) {
            ETRACE("echo() failed");
        }

        close(sock_fd);
    }

    close(serv_fd);
    return 0;
}
