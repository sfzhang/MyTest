#include "quick.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QCursor>
#include <QPixmap>
#include <utility>
#include <iterator>

using namespace std;

Quick::Quick(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setFlag(ItemAcceptsInputMethod, true);

    setPerformanceHint(QQuickPaintedItem::FastFBOResizing);
    //setRenderTarget(QQuickPaintedItem::FramebufferObject);

    QPixmap cursor_pixmap(":/cursor.png");
    setCursor({cursor_pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation), 2, 2});

    connect(this, &QQuickItem::widthChanged, this, &Quick::onWidthChanged);
    connect(this, &QQuickItem::heightChanged, this, &Quick::onHeightChanged);
}

void Quick::drawRing(QPainter *painter, const Ring &ring)
{
    if (!ring.empty()) {
        for (int i = 0; i < ring.size(); i++) {
            painter->drawRect(QRectF(ring[i].x() - 2, ring[i].y() - 2, 4, 4));

            if (i > 0) {
                painter->drawLine(ring[i], ring[i - 1]);
            }
        }
        std::begin(ring);
    }
}

void Quick::paint(QPainter *painter)
{
    painter->save();

    painter->setPen(QColor(128, 0, 0));
    painter->setBrush(QBrush(QColor(0, 128, 0)));

    for (const auto &ring: m_ring_list) {
        drawRing(painter, ring);
    }

    if (!m_current_ring.empty()) {
        bool pop = false;
        if (m_current_ring.back() != m_current_point) {
            m_current_ring.push_back(m_current_point);
            pop = true;
        }

        drawRing(painter, m_current_ring);

        if (pop) {
            m_current_ring.pop_back();
        }
    }

    painter->drawEllipse(0, 0, 50, 50);

    QPen pen(QColor(0, 255, 255));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(50, 50, 300, 300);

    painter->restore();
}

void Quick::mousePressEvent(QMouseEvent *event)
{
    m_current_ring.push_back(event->localPos());
    m_current_point = event->localPos();
    update();
}

void Quick::mouseMoveEvent(QMouseEvent *event)
{
    m_current_point = event->localPos();

    if (!m_current_ring.empty()) {
        update();
    }
}

void Quick::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_ring_list.push_back(std::move(m_current_ring));
    m_current_ring.clear();

    update();
}

void Quick::hoverMoveEvent(QHoverEvent *event)
{
    /*
    m_current_point = event->posF();

    if (!m_current_ring.empty()) {
        update();
    }
    */
}

void Quick::hoverEnterEvent(QHoverEvent *event)
{
    qDebug() << "enter";
}

void Quick::hoverLeaveEvent(QHoverEvent *event)
{
    qDebug() << "leave";
}

void Quick::onWidthChanged()
{
    qDebug() << "onWidthChanged: " << size();
}

void Quick::onHeightChanged()
{
    qDebug() << "onHeightChanged: " << size();
}
