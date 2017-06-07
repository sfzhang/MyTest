#include <QtCore/QCoreApplication>
#include <QLocalSocket>
#include <QDebug>
#include <QString>

#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        qDebug() << "socket() failed: errno[" << errno << "]";
        return -1;
    }


    struct sockaddr_un addr;
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, sizeof(addr.sun_path), "/home/fus/Git/hifu/sock/qtsock");

    socklen_t length = sizeof(addr);
    if (bind(fd, (struct sockaddr*)&addr, length) != 0) {
        qDebug() << "bind() failed: errno: " << errno;
        return -1;
    }

    snprintf(addr.sun_path, sizeof(addr.sun_path), "/home/fus/Git/hifu/sock/mq");
    int ret = connect(fd, (struct sockaddr*)&addr, length);
    if (ret != 0) {
        qDebug() << "connect() failed: errno: " << errno;
        return -1;
    }

    QLocalSocket socket;
    //if (!socket.setSocketDescriptor(qintptr(fd), QLocalSocket::UnconnectedState)) {
    if (!socket.setSocketDescriptor(qintptr(fd))) {
        qDebug() << "setSocketDescriptor() failed";
        return -1;
    }
    qDebug() << "setSocketDescriptor() success";

    /*
    socket.connectToServer("/home/fus/Git/hifu/sock/mq");
    if (socket.waitForConnected(-1)) {
        qDebug() << "connect success";
    }
    else {
        qDebug() << "connect failed";
    }
    */

    char buffer[1024] = {0};
    memset(buffer, 'a', 1024);
    socket.write(buffer, 1024);
    return app.exec();
}
