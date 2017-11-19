#include "dial.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <cmath>
#include <pub/point3d.h>

using namespace std;

double K_INIT_ANGLE_DEG = 150;
double K_RANGE_ANGLE_DEG = 240;
double K_INIT_ANGLE = (M_PI * K_INIT_ANGLE_DEG / 180);
double K_RANGE_ANGLE = (M_PI * K_RANGE_ANGLE_DEG / 180);

Dial::Dial(QWidget *parent):
    QAbstractSlider(parent),
    m_dft_value(0),
    m_has_dft_value(true),
    m_show_notch_value(true),
    m_show_dft_value(true),
    m_adjust(false)
{
    initialize();
    setMouseTracking(true);

    setMinimum(200);
    setMaximum(1000);
    setValue(450);
    m_dft_value = 610;

    setStyleSheet("background-color:#2A2A2A;");

    setMinimumSize(256, 256);
    setMaximumSize(542, 542);
}

Dial::~Dial()
{
}

void Dial::initialize()
{
    /* Panel */
    QIcon *panel = new QIcon(":res/dial_panel.png");

    m_panel_icon.setIcon(panel);
    m_panel_icon.setSize(QSizeF(542, 542));
    m_panel_icon.setInnerRadius(140);
    m_panel_icon.setOuterRadius(220);

    /* Switch */
    QIcon *dial_switch = new QIcon(":res/dial_switch.png");

    m_switch_icon.setIcon(dial_switch);
    m_switch_icon.setSize(QSizeF(542, 542));
    m_switch_icon.setInnerRadius(60);
    m_switch_icon.setOuterRadius(120);

    /* Indicator */
    QIcon *indicator = new QIcon();
    indicator->addFile(":res/dial_indicator_normal.png");
    indicator->addFile(":res/dial_indicator_disabled.png", QSize(), QIcon::Disabled);
    indicator->addFile(":res/dial_indicator_selected.png", QSize(), QIcon::Selected);

    m_indicator_icon.setIcon(indicator);
    m_indicator_icon.setSize(QSizeF(16, 14));

    /* Other radius */
    m_indicator_radius = 74;
    m_tracking_radius = 122;
    m_notch_radius = 155;
    m_notch_value_radius = 180;
    m_dft_value_radius = 205;
}

double Dial::getFontSize(const QString &text, double scale) const
{
    return scale * 32 - 4 * text.length() + 16;
}

double Dial::value2Angle(double value) const
{
    double max = maximum();
    double min = minimum();

    if (value > max) {
        value = max;
    }
    else if (value < min) {
        value = min;
    }

    return (K_INIT_ANGLE + (value - min) / (max - min) * K_RANGE_ANGLE);

}

void Dial::resetIconRegion(const QSize &size)
{
    double scale = 1;

    double w_scale = size.width() / m_panel_icon.getSize().width();
    double h_scale = size.height() / m_panel_icon.getSize().height();

    if (w_scale > h_scale) {
        scale = h_scale;
    }
    else {
        scale = w_scale;
    }

    m_panel_icon.setScale(scale);
    m_panel_icon.setCenter(size.width() / 2.0, size.height() / 2.0);

    m_switch_icon.setScale(scale);
    m_switch_icon.setCenter(size.width() / 2.0, size.height() / 2.0);

    m_indicator_icon.setScale(scale);
}

void Dial::updateValue(const QPointF &point)
{
    QPointF center = m_panel_icon.getCenter();
    auto p = point - center;

    double angle = atan2(p.y(), p.x());
    if (angle < M_PI / 2) {
        angle += 2 * M_PI;
    }

    double min = minimum();
    double max = maximum();
    double old_value = value();

    double new_value = min + (angle - K_INIT_ANGLE) / K_RANGE_ANGLE * (max - min);

    if (((max == old_value) || (min == old_value)) &&
        ((new_value > max) || (new_value < min))) {
        return;
    }

    new_value = qBound(min, new_value, max);
    setSliderPosition(new_value + 0.5);
}

void Dial::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();

    QColor dark(204, 204, 204);
    QColor bright(71, 222, 229);

    double scale = m_panel_icon.getScale();
    QPointF center = m_panel_icon.getCenter();
    double min = minimum();
    double max = maximum();

    /* Draw panel */
    painter.drawPixmap(m_panel_icon.getPosition(), m_panel_icon.getPixmap());

    /* Draw tracking */
    double angle = value2Angle(value());
    double angle_deg = angle * 180 / M_PI;

    QPen pen(bright);
    if (!isEnabled()) {
        pen.setColor(dark);
    }
    pen.setWidth(scale / 0.2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    double r = m_tracking_radius * scale;
    QRectF rect(center.x() - r, center.y() - r, r * 2, r * 2);
    painter.drawArc(rect, -(K_INIT_ANGLE_DEG - 1) * 16,
                          -(angle_deg - K_INIT_ANGLE_DEG + 1) * 16);

    /* Draw notch */
    pen.setWidth(2);
    pen.setColor(dark);
    painter.setPen(pen);

    QBrush brush(dark);
    painter.setBrush(brush);

    double x = 0;
    double y = 0;
    if ((m_show_notch_value) || (m_show_dft_value && m_has_dft_value)) {
        r = m_notch_radius * scale;
    }
    else {
        r = (m_panel_icon.getOuterRadius() + m_panel_icon.getInnerRadius()) / 2 * scale;
    }

    double d = scale / 0.4;
    for (int i = 0; i <= K_RANGE_ANGLE_DEG; i += 30) {
        x = center.x() + r * cos((K_INIT_ANGLE_DEG + i) * M_PI / 180);
        y = center.y() + r * sin((K_INIT_ANGLE_DEG + i) * M_PI / 180);
        painter.drawPie(x - d, y - d, 2 * d, 2 * d, 0, 360 * 16);
    }

    double v = 0;
    r = m_dft_value_radius * scale;
    if (m_has_dft_value && m_show_dft_value) {
        v = value2Angle(m_dft_value);
        x = center.x() + r * cos(v);
        y = center.y() + r * sin(v);

        if (isEnabled()) {
            brush.setColor(bright);
            pen.setColor(bright);
        }
        else {
            brush.setColor(dark);
            pen.setColor(dark);
        }

        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawPie(x - d, y - d, 2 * d, 2 * d, 0, 360 * 16);
    }

    /* Draw switch */
    painter.drawPixmap(m_switch_icon.getPosition(), m_switch_icon.getPixmap());

    /* Draw indicator */
    r = m_indicator_radius * scale;
    x = center.x() + r * cos(angle);
    y = center.y() + r * sin(angle);
    painter.translate(x, y);
    painter.rotate(90 + angle_deg);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    if (!isEnabled()) {
        painter.drawPixmap(m_indicator_icon.getPosition(),
                           m_indicator_icon.getPixmap(QIcon::Disabled));
    }
    else {
        painter.drawPixmap(m_indicator_icon.getPosition(),
                           m_indicator_icon.getPixmap(QIcon::Selected));
    }
    painter.rotate(-(90 + angle_deg));
    painter.translate(-x, -y);

    /* Draw value */
    QString text = QString("%1").arg(value());
    QFont font("Square721 BT", getFontSize(text, scale), QFont::Bold);
    painter.setFont(font);

    if (!isEnabled()) {
        pen.setColor(dark);
    }
    else {
        pen.setColor(bright);
    }
    painter.setPen(pen);

    QRectF text_rect = QRectF(center.x() - 1, center.y() - 1, 2, 2);
    painter.drawText(text_rect, Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                     text);

    /* Draw notch value */
    if (m_show_notch_value) {
        pen.setColor(dark);
        pen.setWidth(2);
        painter.setPen(pen);

        font.setPointSize(scale * 18);
        painter.setFont(font);

        r = m_notch_value_radius * scale;
        for (int i = 0; i <= K_RANGE_ANGLE_DEG; i += 30) {
            if (i / 30 % 2) {
                continue;
            }
            double x = center.x() + r * cos((i + K_INIT_ANGLE_DEG) * M_PI / 180);
            double y = center.y() + r * sin((i + K_INIT_ANGLE_DEG) * M_PI / 180);
            v = min + (max - min) / (K_RANGE_ANGLE_DEG / 30) * 8 * i / 30;

            painter.translate(x, y);
            painter.rotate(K_INIT_ANGLE_DEG + i + 90);
            painter.drawText(QRectF(- 1, - 1, 2, 2), Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                             QString("%1").arg(v));
            painter.rotate(-(K_INIT_ANGLE_DEG + i + 90));
            painter.translate(-x, -y);
        }
    }

    painter.restore();

#if 0



    double value = (m_value - m_min) * 240 / (m_max - m_min);


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

#endif
}

void Dial::resizeEvent(QResizeEvent *event)
{
    resetIconRegion(event->size());
    QAbstractSlider::resizeEvent(event);
}

void Dial::mousePressEvent(QMouseEvent *event)
{
    if ((minimum() == maximum()) || (event->button() != Qt::LeftButton) ||
        (!isEnabled())) {
        event->ignore();
        return;
    }
    else if (m_switch_icon.contains(event->localPos())) {
        event->accept();
        m_adjust = true;
        updateValue(event->localPos());
    }
    else {
        QAbstractSlider::mousePressEvent(event);
    }
}

void Dial::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_adjust) {
        event->accept();
        updateValue(event->localPos());
        m_adjust = false;
    }
    else {
        QAbstractSlider::mousePressEvent(event);
    }
}

void Dial::mouseMoveEvent(QMouseEvent *event)
{
    if (m_adjust) {
        event->accept();
        updateValue(event->localPos());
        update();
    }
    else if (isEnabled() && m_switch_icon.contains(event->localPos())) {
        if (!m_hover_switch) {
            m_hover_switch = true;
            update();
        }
    }
    else {
        if (m_hover_switch) {
            m_hover_switch = false;
            update();
        }
        QAbstractSlider::mouseMoveEvent(event);
    }
}

void Dial::setDefaultValue(int value)
{
    m_dft_value = qBound(minimum(), value, maximum());
    update();
}

void Dial::showDefaultValue(bool enable)
{
    m_show_dft_value = enable;
    update();
}

void Dial::showNotchValue(bool enable)
{
    m_show_notch_value = enable;
    update();
}
