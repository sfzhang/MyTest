#include "widget.h"
#include "ui_widget.h"
#include <QByteArray>
#include <signal.h>
#include <unistd.h>
#include <QMap>

struct T {

    T(int i = 0)
    {
        a = i;
    }

    ~T()
    {
        qDebug() << "de: " << (long)&a;
        a = 100;
    }

    int a;
};

void handle_sigpipe(int signo)
{
    qDebug() << "Receive Signal: " << signo << "\n";
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->m_ip_line_edit->setText("127.0.0.1");
    ui->m_port_line_edit->setText("9999");

    m_socket = new QTcpSocket(this);

    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(m_socket, &QAbstractSocket::readyRead,
            this, &Widget::receive);
    connect(m_socket, &QAbstractSocket::disconnected,
            this, &Widget::closeSocket);

    connect(ui->m_connect_btn, &QPushButton::clicked,
            this, &Widget::on_socket_button_clicked);
    connect(ui->m_send_btn, &QPushButton::clicked,
            this, &Widget::on_send_button_clicked);

    signal(SIGPIPE, handle_sigpipe);

    QMap<int, T> map;
    for (int i = 0; i < 10; i++) {
        map[i] = T(i);
    }


    int i = 0;
    for (QMutableMapIterator<int, T> it(map); it.hasNext(); ) {
        it.next();
        qDebug() << it.value().a;
        qDebug() << "begin remove: " << long(&it.value().a);
        map.remove(it.key());
        qDebug() << "end remove: " << map.size() << long(&it.value().a);
        qDebug() << it.value().a;

        /*
        if (i > 0) {
            qDebug() << "Prev: " << it.peekPrevious().value().a;
        }
        i++;
        */
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_socket_button_clicked()
{
    if (ui->m_connect_btn->text() == "Connect") {
        connectSocket();
    }
    else {
        closeSocket();
    }
}

void Widget::on_send_button_clicked()
{
    QByteArray data(1024, 'a');
    //data.append(ui->m_send_line_edit->text());

    for (int i = 0; i < 1000000; i++) {
        m_socket->write(data);
        if (m_socket->state() == QAbstractSocket::ConnectedState) {
            usleep(1000);
            m_socket->flush();
            qDebug() << i << ")signal: " <<
                      (int*)signal(SIGPIPE, handle_sigpipe) << "\n";
            m_socket->waitForBytesWritten(-1);
        }
        else {
            break;
        }
    }
}

void Widget::socketError(QAbstractSocket::SocketError socketError)
{
    QString msg = QString("TCP Socket error occured: errno[%1], msg[%2]")
                    .arg(socketError)
                    .arg(m_socket->errorString());
    ui->m_msg_label->setText(msg);
    closeSocket();
}

void Widget::receive()
{
    QByteArray data = m_socket->readAll();
    ui->m_msg_label->setText(QString::fromStdString(data.toStdString()));
}

void Widget::connectSocket()
{
    m_socket->connectToHost(ui->m_ip_line_edit->text(),
                            ui->m_port_line_edit->text().toInt());
    if (!m_socket->waitForConnected()) {
        ui->m_msg_label->setText("Connect failed!");
        m_socket->close();
    }
    else {
        ui->m_msg_label->setText("Connect success!");
        ui->m_ip_line_edit->setEnabled(false);
        ui->m_port_line_edit->setEnabled(false);
        ui->m_connect_btn->setText("Disconnect");
        ui->m_send_line_edit->setText("");
        ui->m_send_line_edit->setEnabled(true);
        ui->m_send_btn->setEnabled(true);
    }
}

void Widget::closeSocket()
{
    m_socket->close();
    ui->m_ip_line_edit->setEnabled(true);
    ui->m_port_line_edit->setEnabled(true);
    ui->m_connect_btn->setText("Connect");
    ui->m_send_line_edit->setText("");
    ui->m_send_line_edit->setEnabled(false);
    ui->m_send_btn->setEnabled(false);
}
