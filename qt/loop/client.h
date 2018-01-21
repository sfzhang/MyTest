#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client: public QObject
{
    Q_OBJECT

public:

    Client();

    virtual bool event(QEvent *);

protected slots:

    void handleConnection();

protected:

    QTcpSocket *m_socket;

};

#endif // CLIENT_H
