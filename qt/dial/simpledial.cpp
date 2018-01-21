/**
 * @file Simple dial implement
 *
 * @author sfzhang
 * @date 2017-11-21
 */

#include "simpledial.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <cmath>
#include <pub/point3d.h>

using namespace std;

const QColor SimpleDial::K_REC_COLOR = QColor(0, 255, 0);

SimpleDial::SimpleDial(int min, int max, int rec, QWidget *parent):
    Dial(min, max, rec, parent)
{
    /* Call initialize() to override some icon */
    initialize();
}

SimpleDial::SimpleDial(int min, int max, QWidget *parent):
    SimpleDial(min, max, (min + max) / 2, parent)
{
}

void SimpleDial::initialize()
{
    /* NOT good :( */

    /* Reset switch */
    QIcon *dial_switch = new QIcon(":res/dial_rec_switch.png");
    m_switch_icon.setIcon(dial_switch);
    m_switch_icon.setSize(QSizeF(480, 480));
    m_switch_icon.setInnerRadius(54);
    m_switch_icon.setOuterRadius(82.5);

    /* Reset default button */
    QIcon rec_icon;
    rec_icon.addFile(":res/dial_rec_normal.png");
    rec_icon.addFile(":res/dial_rec_disabled.png", QSize(), QIcon::Disabled);
    rec_icon.addFile(":res/dial_rec_active.png", QSize(), QIcon::Active);
    rec_icon.addFile(":res/dial_rec_selected.png", QSize(), QIcon::Selected);
    delete m_dft_btn;
    m_dft_btn = new CircularButton(32, 72, rec_icon, "", this);
    connect(m_dft_btn, &QPushButton::clicked, this, &SimpleDial::setDefault);

    /* Other radius */
    m_indicator_radius = 64.5;
}

double SimpleDial::getFontSize(const QString &text, double scale) const
{
    return scale * 18 - 3 * text.length() + 14;
}

void SimpleDial::drawNotch(QPainter &painter)
{
    Dial::drawNotch(painter);

    double angle = value2Angle(m_dft_value);

    painter.save();

    QPen pen(K_REC_COLOR);
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(K_REC_COLOR);
    painter.setBrush(brush);

    double r = m_notch_radius * m_panel_icon.getScale();
    QPointF center = m_panel_icon.getCenter();
    double x = center.x() + r * cos(angle);
    double y = center.y() + r * sin(angle);
    double d = m_panel_icon.getScale() / 0.4;

    painter.drawPie(x - d, y - d, 2 * d, 2 * d, 0, 360 * 16);

    painter.restore();
}

void SimpleDial::drawValue(QPainter &painter)
{
    painter.save();

    QString text = QString("%1").arg(value());
    double size = getFontSize(text, m_panel_icon.getScale());

    QFont font("Square721 BT", size, QFont::Bold);
    painter.setFont(font);

    if (!isEnabled()) {
        painter.setPen(K_DARK_COLOR);
    }
    else {
        painter.setPen(K_BRIGHT_COLOR);
    }

    QPointF center = m_panel_icon.getCenter();
    QRectF text_rect = QRectF(center.x() - 1, center.y() + 2, 2, 2);
    painter.drawText(text_rect, Qt::AlignBottom | Qt::AlignHCenter | Qt::TextSingleLine | Qt::TextDontClip,
                     text);

    int range = m_dft_value - minimum();
    int v = range ? (100 * (value() - minimum()) / range) : 0;
    text = QString("%1%").arg(v);
    size *= 0.75;
    font.setPointSize(size);
    painter.setFont(font);

    text_rect = QRectF(center.x() - 1, center.y() + 2, 2, 2);
    painter.drawText(text_rect, Qt::AlignTop | Qt::AlignHCenter | Qt::TextSingleLine | Qt::TextDontClip,
                     text);

    painter.restore();
}

void SimpleDial::drawNotchValue(QPainter &painter)
{
    double angle = value2Angle(m_dft_value);
    double angle_deg = angle * 180 / M_PI;

    painter.save();

    QPointF center = m_panel_icon.getCenter();

    QPen pen(K_REC_COLOR);
    pen.setWidth(2);
    painter.setPen(pen);

    QFont font("Square721 BT", (m_panel_icon.getScale() * 16), QFont::Normal);
    painter.setFont(font);

    double r = m_notch_value_radius * m_panel_icon.getScale();
    double x = center.x() + r * cos(angle);
    double y = center.y() + r * sin(angle);

    painter.translate(x, y);
    painter.rotate(angle_deg + 90);
    painter.drawText(QRectF(- 1, - 1, 2, 2), Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                     "R");
    painter.rotate(-(angle_deg + 90));
    painter.translate(-x, -y);

    painter.restore();
}
