#include "dialog.h"
#include "ui_dialog.h"
#include <QMouseEvent>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_move_widget(false)
{
    ui->setupUi(this);
    setStyleSheet("background: yellow");
    setMouseTracking(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    QRect title_bar(0, 0, width(), 48);

    if (title_bar.contains(event->pos())) {
        qDebug() << "press pos: (" << pos().x() << ", " << pos().y() << "), global_pos: ("
                 << event->globalX() << ", " << event->globalY() << "), prev_pos: ("
                 << m_prev_point.x() << ", " << m_prev_point.y() << ")\n";

        m_orig_point = pos();
        m_prev_point = event->globalPos();
        m_move_widget = true;
        grabMouse(Qt::ClosedHandCursor);
    }
    else {
        QDialog::mousePressEvent(event);
    }
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move_widget) {
        qDebug() << "pos: (" << pos().x() << ", " << pos().y() << "), global_pos: ("
                 << event->globalX() << ", " << event->globalY() << "), prev_pos: ("
                 << m_prev_point.x() << ", " << m_prev_point.y() << ")\n";

        move(m_orig_point + event->globalPos() - m_prev_point);
        //m_prev_point = event->globalPos();
    }
    else {
        QDialog::mouseMoveEvent(event);
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_move_widget) {
        m_move_widget = false;
        releaseMouse();
    }
    else {
        QDialog::mouseReleaseEvent(event);
    }
}
