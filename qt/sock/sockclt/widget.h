#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QAbstractSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected slots:

    void on_socket_button_clicked();

    void on_send_button_clicked();

    void receive();

    void socketError(QAbstractSocket::SocketError socketError);

    void connectSocket();

    void closeSocket();

private:
    Ui::Widget *ui;
    QTcpSocket *m_socket;
};

#endif // WIDGET_H
