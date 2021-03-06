/**
 * @brief Dial button
 *
 * @author sfzhang
 * @date 2017-11-20
 */

#include "circularbutton.h"
#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QStyleOption>
#include <QCursor>
#include <QMouseEvent>

CircularButton::CircularButton(double radius, double length, const QIcon &icon,
                               const QString &text, QWidget *parent):
    QPushButton(icon, text, parent),
    m_radius(radius),
    m_length(length),
    m_hover(false)
{
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);
}

CircularButton::~CircularButton()
{
}

void CircularButton::getStatus(QIcon::Mode &mode, QIcon::State &state) const
{
    mode = isEnabled() ? QIcon::Normal : QIcon::Disabled;
    if (QIcon::Normal == mode) {
        if (isDown()) {
            mode = QIcon::Selected;
        }
        else if (m_hover) {
            mode = QIcon::Active;
        }
    }

    state = isCheckable() && isChecked() ? QIcon::On : QIcon::Off;
    if (isChecked()) {
        mode = QIcon::Normal;
    }
}

void CircularButton::getGeometry(double &x, double &y, double &length) const
{
    if (width() > height()) {
        x = (width() - height()) / 2.0;
        y = 0;
        length = height();
    }
    else {
        x = 0;
        y = (height() - width()) / 2.0;
        length = width();
    }
}

QSize CircularButton::sizeHint() const
{
    return QSize(m_length, m_length);
}

QSize CircularButton::minimumSizeHint() const
{
    return QSize(m_length / 4, m_length / 4);
}

bool CircularButton::hitButton(const QPoint &pos) const
{
    QPoint vec = pos - rect().center();
    double length = qMin(width(), height());
    double r = m_radius * length / m_length;

    return ((vec.x() * vec.x() + vec.y() * vec.y()) <= (r * r));
}

void CircularButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QIcon::Mode mode = QIcon::Normal;
    QIcon::State state = QIcon::Off;
    getStatus(mode, state);

    double x = 0;
    double y = 0;
    double length = 0;
    getGeometry(x, y, length);

    QPixmap pixmap = icon().pixmap(length, mode, state);
    QPainter painter(this);
    painter.drawPixmap(x, y, pixmap);
}

void CircularButton::mouseMoveEvent(QMouseEvent *event)
{
    QStyleOption opt;
    opt.init(this);

    bool hover = (opt.state & QStyle::State_MouseOver) &&
                 (hitButton(event->localPos().toPoint()));
    if (hover != m_hover) {
        m_hover = hover;
        update();
    }

    QPushButton::mouseMoveEvent(event);
}

void CircularButton::leaveEvent(QEvent *event)
{
    if (m_hover) {
        m_hover = false;
        update();
    }

    QPushButton::leaveEvent(event);
}
