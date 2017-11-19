#include "dial.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <cmath>
#include <pub/point3d.h>
#include <QAbstractSlider>
#include <private/qabstractslider_p.h>

using namespace std;

Dial::Dial(QWidget *parent):
    QDial(parent),
    m_x(0),
    m_y(0),
    m_length(0),
    m_adjust(false),
    m_value(400),
    m_min(200),
    m_max(1000)
{
    m_panel = new QIcon(":res/dial_panel.png");
    m_switch = new QIcon(":res/dial_switch.png");
    m_cursor = new QIcon(":res/dial_cursor_selected.png");

    setStyleSheet("background-color:#2A2A2A;");

    setMinimumSize(256, 256);
    setMaximumSize(542, 542);
}

Dial::~Dial()
{

}

void Dial::resetIconRegion(const QSize &size)
{
    if (size.width() > size.height()) {
        m_length = size.height();
        m_y = 0;
        m_x = (size.width() - size.height()) / 2;
    }
    else {
        m_length = size.width();
        m_x = 0;
        m_y = (size.height() - size.width()) / 2;
    }
}

void Dial::setValue(const QPointF &point)
{
    QPointF center = QRectF(m_x, m_y, m_length, m_length).center();
    auto p = point - center;

    double angle = atan2(p.y(), p.x());
    if (angle < M_PI / 2) {
        angle += 2 * M_PI;
    }

    double value = m_min + (angle * 180 / M_PI - 150) / 240 * (m_max - m_min);

    if (((m_max == m_value) || (m_min == m_value)) &&
        ((value > m_max) || (value < m_min))) {
        return;
    }

    m_value = value;
    if (m_value > m_max) {
        m_value = m_max;
    }
    else if (m_value < m_min) {
        m_value = m_min;
    }
}

void Dial::paintEvent(QPaintEvent *)
{
    double value = (m_value - m_min) * 240 / (m_max - m_min);

    QPainter painter(this);

    painter.drawPixmap(m_x, m_y, m_panel->pixmap(m_length));

    QPointF center = QRectF(m_x, m_y, m_length, m_length).center();

    double length = 248 * m_length / 542.0;
    QRectF rect(center.x() - length / 2, center.y() - length / 2,
                length, length);

    QPen pen;
    pen.setColor(QColor(71, 222, 229));
    pen.setWidth(3);

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.drawArc(rect, -149 * 16, -(value + 1)* 16);
    pen.setWidth(2);
    pen.setColor(QColor(204, 204, 204));
    painter.setPen(pen);

    QBrush brush(QColor(204, 204, 204));
    painter.setBrush(brush);

    double r = 160 * m_length / 542.0;
    for (int i = 150; i <= 390; i += 30) {
        double x = center.x() + r * cos(i * M_PI / 180);
        double y = center.y() + r * sin(i * M_PI / 180);

        painter.drawPie(x - 1, y - 1, 2, 2, 0, 360 * 16);
    }

    painter.restore();

    painter.drawPixmap(m_x, m_y, m_switch->pixmap(m_length));

    painter.save();
    pen.setColor(QColor(71, 222, 229));
    pen.setWidth(2);
    painter.setPen(pen);

    length = 100 * m_length / 542.0;

    QFont font("Square721 BT", length / 3, QFont::Bold);
    painter.setFont(font);

    QRect text_rect = QRect(center.x() - length / 2, center.y() - length / 2,
                            length, length);
    painter.drawText(text_rect, Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                     QString("%1").arg((int)m_value));

    painter.restore();

    length = 20 * m_length / 542.0;
    r = 74 * m_length / 542.0;
    double x = center.x() + r * cos((150 + value) * M_PI / 180);
    double y = center.y() + r * sin((150 + value) * M_PI / 180);
    painter.translate(x, y);
    painter.rotate((90 + 150 + value));
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(QPointF(-length / 2.0, -length / 2.0), m_cursor->pixmap(length));
    painter.rotate(-(90 + 150 + value));
    painter.translate(-x, -y);

    QFont font1("Square721 BT", m_length / 25, QFont::Normal);
    painter.setFont(font1);

    painter.save();
    pen.setColor(QColor(204, 204, 204));
    pen.setWidth(2);
    painter.setPen(pen);

    r = 190 * m_length / 542.0;
    for (int i = 150; i <= 390; i += 30) {
        if ((i - 150) / 30 % 2) {
            continue;
        }
        double x = center.x() + r * cos(i * M_PI / 180);
        double y = center.y() + r * sin(i * M_PI / 180);

        painter.translate(x, y);
        painter.rotate(i + 90);
        painter.drawText(QRectF(- 1, - 1, 2, 2), Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                         QString("%1").arg(m_min + (m_max - m_min) / 8.0 * (i - 150) / 30));
        painter.rotate(-(i + 90));
        painter.translate(-x, -y);
    }
    painter.restore();
}

void Dial::resizeEvent(QResizeEvent *event)
{
    resetIconRegion(event->size());
    QDial::resizeEvent(event);
}

void Dial::mousePressEvent(QMouseEvent *event)
{
    QPointF center = QRectF(m_x, m_y, m_length, m_length).center();
    QPointF d = event->localPos() - center;
    double distance = sqrt(d.x() * d.x() + d.y() * d.y());

    if ((distance >= (60 * m_length / 542.0)) &&
        (distance <= (120 * m_length / 542.0))) {
        m_adjust = true;
        setValue(event->localPos());
    }

    QDial::mousePressEvent(event);
}

void Dial::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_adjust) {
        setValue(event->localPos());
        m_adjust = false;
    }

    QDial::mousePressEvent(event);
}

void Dial::mouseMoveEvent(QMouseEvent *event)
{
    if (m_adjust) {
        setValue(event->localPos());
        update();
    }

    QDial::mouseMoveEvent(event);
}
