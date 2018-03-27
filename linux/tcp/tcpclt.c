#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include "trace.h"

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

    char buffer[1024] = {0};
    ssize_t size = 0;
    char *ptr = NULL;

    while (ptr = fgets(buffer, 1024, stdin)) {
        size = write(sock_fd, buffer, strlen(buffer));
        if (size != strlen(buffer)) {
            ETRACE("write() failed: errno[%d]", errno);
            return -1;
        }
        memset(buffer, 0, sizeof(buffer));
    }

    if (!ptr) {
        ETRACE("fgets() failed: errno[%d]", errno);
    }


    /*
    unsigned long i = 0;
    while (1) {
        snprintf(buffer, sizeof(buffer), "%lu", i);
        i++;

        size = write(sock_fd, buffer, strlen(buffer));
        if (size != strlen(buffer)) {
            ETRACE("write() failed: errno[%d]", errno);
            return -1;
        }

        sleep(2);
    }
    */

    return 0;
}
