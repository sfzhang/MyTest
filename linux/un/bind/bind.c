#include "trace.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf ("usage: %s pathname\n", argv[0]);
        return -1;
    }

    int sock_fd = -1;
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd < 0) {
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

    int ret = bind(sock_fd, (struct sockaddr *)&addr_serv, SUN_LEN(&addr_serv));
    if (ret != 0) {
        ETRACE("bind() failed: errno[%d]", errno);
        return -1;
    }

    struct sockaddr_un addr_bind;
    bzero(&addr_bind, sizeof(addr_bind));
    socklen_t length = sizeof(addr_bind);
    ret = getsockname(sock_fd, (struct sockaddr *)&addr_bind, &length);
    if (ret != 0) {
        ETRACE("getsockname() failed: errno[%d]", errno);
        return -1;
    }

    DTRACE("bound name[%s], length[%d]", addr_bind.sun_path, length);
    return 0;
}


    
