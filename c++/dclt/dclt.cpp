/**
 * @file dits client
 *
 * @author sfzhang
 * @date 2017-6-6
 */

#include "trace.h"
#include "imgxfer.pb.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <poll.h>
#include <iostream>
#include <fcntl.h>

using namespace std;
using namespace imgxfer::proto;

struct proto_t {
    proto_t(UiOption opt = MOUSE_CLICK, int seq = 1, const string &r = "", int _x = -1, int _y = -1, const string &v = "", int s = -1):
        option(opt), sequence(seq), res(r), x(_x), y(_y), value(v), sleep(s) {}
    UiOption option;
    int sequence;
    string res;
    int x;
    int y;
    string value;
    int sleep;
};

/**
 * @brief Print usage
 */
static void usage()
{
    cout << "./dclt" << endl;
}

int readn(int fd, void *buf, size_t &size, int timeout)
{
    if (fd < 0) {
        ETRACE("argument illegal: fd[%d]", fd);
        return -1; 
    }   

    if (NULL == buf) {
        ETRACE("argumnet illegal: buf[%#lx]", buf);
        return -1; 
    }   

    if (timeout < -1) {
        ETRACE("argumnet illegal: timeout[%#lx]", timeout);
        return -1; 
    }

    struct pollfd fds;
    memset(&fds, 0, sizeof(fds));
    fds.fd = fd;
    fds.events = POLLIN;

    size_t read_length = 0;
    int ret = 0;
    while (read_length < size) {
        ret = poll(&fds, (sizeof(fds) / sizeof(struct pollfd)), timeout);
        if (ret < 0) {
            ETRACE("poll() failed: errno[%d]", errno);

            size = read_length;
            return -1;
        }
        else if (0 == ret) {
            ETRACE("poll() timeout");
            size = read_length;
            return 0;
        }

        if (fds.revents & (!POLLIN)) {
            ETRACE("poll() success, but error occur, revents[%x]", fds.revents);

            size = read_length;
            return -1;
        }
        else if (fds.revents & POLLIN) {
            ret = read(fd, (reinterpret_cast<char *>(buf) + read_length),
                       (size - read_length));
            if (ret < 0) {
                ETRACE("read() failed: errno[%d]", errno);

                size = read_length;
                return -1;
            }
            else if (0 == ret) {
                ETRACE("read() failed: connection closed by peer");

                size = read_length;
                return -1;
            }

            read_length += ret;
        }
    }

    size = read_length;
    return 1;
}

/**
 * @brief Send to dits
 */
static bool send_to_dits(int fd, const proto_t &proto)
{
    ImgXferMsg ixm;

    ixm.set_type(IMG_XFER_UI);
    ixm.mutable_ui()->set_option(proto.option);
    ixm.mutable_ui()->set_sequence(proto.sequence);
    if (!proto.value.empty()) {
        ixm.mutable_ui()->set_input(proto.value);
    }
    if ((proto.x >= 0) && (proto.y >= 0)) {
        ixm.mutable_ui()->mutable_position()->set_x(proto.x);
        ixm.mutable_ui()->mutable_position()->set_y(proto.y);
    }
    if (!proto.res.empty()) {
        ixm.mutable_ui()->set_resource(proto.res);
    }
    if (proto.sleep > 0) {
        ixm.mutable_ui()->set_sleep_time(proto.sleep);
    }

    int size = ixm.ByteSize();
    char *data = new char[size + sizeof(uint32_t) * 2];

    *reinterpret_cast<uint32_t *>(data) = htonl(size + sizeof(uint32_t));
    *(reinterpret_cast<uint32_t *>(data) + 1) = 0;
    if (!ixm.SerializeToArray(data + 2 * sizeof(uint32_t), size)) {
        ETRACE("SerializeToArray() failed!");
        delete [] data;
        return false;
    }
    size += sizeof(uint32_t) * 2;

    if (send(fd, data, size, 0) != size) {
        ETRACE("send() failed: errno[%d]", errno);
        delete [] data;
        return false;
    }

    delete [] data;
    return true;
}

/**
 * @brief Receive from dits
 */
static bool recv_from_dits(int fd)
{
    char buffer[1024] = {0};
    uint32_t length = 0;
    size_t size = 0;
    uint32_t type = 0;

    while (1) {
        /* Read length */
        size = 4;
        if (readn(fd, &length, size, -1) != 1) {
            ETRACE("readn() length failed");
            return false;
        }

        length = ntohl(length);
        if ((length > 1024) || (length <= 4)) {
            ETRACE("Invalid length[%u]", length);
            return false;
        }

        size = length;
        if (readn(fd, buffer, size, -1) != 1) {
            ETRACE("readn() data failed!");
            return false;
        }

        type = *reinterpret_cast<uint32_t *>(buffer);
        type = ntohl(type);
        DTRACE("type[%u]", type);

        if (0 == type) {
            ImgXferMsg ixm;
            if (!ixm.ParseFromArray(buffer + sizeof(uint32_t), (length - sizeof(uint32_t)))) {
                ETRACE("ParseFromArray() failed");
                return false;
            }

            if (ixm.type() == IMG_XFER_ACK) {
                ITRACE("ACK[%u]", ixm.ack_value());
            }
        }
    }

    return true;
}

/**
 * @brief main
 */
int main(int argc, char *argv[])
{
    /* Parse arguments */
    string server = "127.0.0.1";
    uint16_t port = 8888;

    /* Create socket */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        ETRACE("socket() failed: errno[%d]", errno);
        return -1;
    }

    /* Connect to server */
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(server.c_str());
    serv_addr.sin_port = htons(port);
    int ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret != 0) {
        ETRACE("connect() failed: server[%s], port[%hu]", server.c_str(), port);
        return -1;
    }
    DTRACE("connect() success: server[%s], port[%hu]", server.c_str(), port);

    /* Send */
    /* S1 */
    send_to_dits(sockfd, {MOUSE_CLICK,  1,   "trigger",  29,    7,    "",            1000});
    send_to_dits(sockfd, {MOUSE_CLICK,  1,   "out4",     -1,    -1,   "",            -1});
    send_to_dits(sockfd, {MOUSE_CLICK,  1,   "a",        0,     0,    "",            500});
    send_to_dits(sockfd, {MOUSE_CLICK,  1,   "",         5,     5,    "",            300});
    send_to_dits(sockfd, {RIGHT_CLICK,  1,   "title",   -1,    -1,   "",            400});
    send_to_dits(sockfd, {INPUT,        1,   "ec",       81,    6,    "74",          1000});
    send_to_dits(sockfd, {MOUSE_CLICK,  1,   "",         0,     0,    "",            500});
    send_to_dits(sockfd, {DOUBLE_CLICK, 2,   "t3",       50,    5,   "",            100});
    send_to_dits(sockfd, {MOUSE_CLICK,  2,   "",         0,     0,    "",            500});

    recv_from_dits(sockfd);

    close(sockfd);

    return 0;
}
