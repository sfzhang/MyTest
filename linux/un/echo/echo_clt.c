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
    if (argc != 3) {
        printf ("usage: %s string\n", argv[0]);
        return -1;
    }

    int sock_fd = -1;
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        ETRACE("socket() failed: errno[%d]", errno);
        return -1;
    }

    struct sockaddr_un addr_clt;
    bzero(&addr_clt, sizeof(addr_clt));
    addr_clt.sun_family = AF_UNIX;
    snprintf(addr_clt.sun_path, sizeof(addr_clt.sun_path), "./%s.un", argv[0]);
    socklen_t length = sizeof(addr_clt);
    if (bind(sock_fd, (struct sockaddr*)&addr_clt, length) != 0) {
        ETRACE("bind() failed: errno[%d]", errno);
        return -1;
    }

    struct sockaddr_un addr_serv;
    bzero(&addr_serv, sizeof(addr_serv));
    addr_serv.sun_family = AF_UNIX;
    snprintf(addr_serv.sun_path, sizeof(addr_serv.sun_path), "%s", argv[1]);

    length = sizeof(addr_serv);
    int ret = connect(sock_fd, (struct sockaddr*)&addr_serv, length);
    if (ret != 0) {
        ETRACE("connect() failed: errno[%d]", errno);
        return -1;
    }

    char buffer[MAX_LINE] = {0};
    snprintf(buffer, sizeof(buffer), "%s", argv[2]);
    if (write(sock_fd, buffer, strlen(buffer)) != strlen(buffer)) {
        ETRACE("write() failed: errno[%d]", errno);
        return -1;
    }

    bzero(buffer, sizeof(buffer));
    if (read(sock_fd, buffer, sizeof(buffer) - 1) < 0) {
        ETRACE("read() failed: errno[%d]", errno);
        return -1;
    }

    printf("%s\n", buffer);
    return 0;
}
