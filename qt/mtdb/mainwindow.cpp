#include "mainwindow.h"
#include "mtconn.h"
#include <thread/thread.h>
#include <dbsql/idbconnection.h>
#include <QHBoxLayout>

using namespace hifu;
using namespace hifu::thread;

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent)
{
    m_line_edit = new QLineEdit("10");
    m_create_btn = new QPushButton("create");
    m_start_btn = new QPushButton("start");
    m_quit_btn = new QPushButton("quit");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_line_edit);
    layout->addWidget(m_create_btn);
    layout->addStretch(1);
    layout->addWidget(m_start_btn);
    layout->addStretch(1);
    layout->addWidget(m_quit_btn);

    setLayout(layout);

    connect(m_create_btn, &QPushButton::clicked, this, &MainWindow::on_create);

    dbsql::IDbConnection::instance()->enableMultiThread();
}

void MainWindow::on_create()
{
    int count = m_line_edit->text().toInt();
    if (count <= 0) {
        count = 10;
    }

    for (int i = 0; i < count; i++) {
        QString tn = QString("mtconn_%1").arg(i);
        Thread *t = new Thread(tn);

        MtConn *mtconn = new MtConn;
        mtconn->moveToThread(t);

        connect(m_start_btn, &QPushButton::clicked, mtconn, &MtConn::connect);
        connect(m_quit_btn, &QPushButton::clicked, mtconn, &MtConn::quit);

        t->start();
    }
}
