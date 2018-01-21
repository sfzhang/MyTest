#include "client.h"
#include <QCoreApplication>
#include <QEvent>

Client::Client()
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Client::handleConnection);
    m_socket->connectToHost("127.0.0.1", 9760);
}

void Client::handleConnection()
{
    QEvent *e = new QEvent(QEvent::Type::None);
    QCoreApplication::postEvent(this, e);
}

bool Client::event(QEvent *)
{
    qDebug() << "Receive event!" << endl;
}

