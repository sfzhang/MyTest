#include "quick.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QCursor>
#include <QPixmap>
#include <utility>
#include <iterator>
#include <dicm/dicminstance.h>

using namespace std;
using namespace hifu;
using namespace hifu::dicm;

Quick::Quick(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setFlag(ItemAcceptsInputMethod, true);
    setOpaquePainting(true);

    setPerformanceHint(QQuickPaintedItem::FastFBOResizing);
    //setRenderTarget(QQuickPaintedItem::FramebufferObject);

    QPixmap cursor_pixmap(":/cursor.png");
    setCursor({cursor_pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation), 2, 2});

    connect(this, &QQuickItem::widthChanged, this, &Quick::onWidthChanged);
    connect(this, &QQuickItem::heightChanged, this, &Quick::onHeightChanged);

    auto dicm_inst = DicmInstance::createObject();
    if (dicm_inst->loadFromFile("/home/fus/Exp/insightec/002_plan_1/I.001") != DicmState::FAILED) {
        dicm_inst->setMinMaxWindow();
        unsigned long width = 0, height = 0;

        if (dicm_inst->getImageSize(width, height)) {
            m_dicom_image = QImage(static_cast<int>(width), static_cast<int>(height), QImage::Format_ARGB32);

            const uint8_t *pixel = reinterpret_cast<const uint8_t *>(dicm_inst->getOutputData(8));
            if (pixel) {
                uint8_t *bits = m_dicom_image.bits();
                for (unsigned long i = 0; i < height; i++) {
                    for (unsigned long j = 0; j < width; j++) {
                        *bits++ = *pixel;
                        *bits++ = *pixel;
                        *bits++ = *pixel;
                        *bits++ = 0xFF;
                        pixel++;
                    }
                }
            }
        }
    }
}

void Quick::drawImage(QPainter *painter)
{
    auto win_w = width();
    auto win_h = height();

    auto img_w = m_dicom_image.width();
    auto img_h = m_dicom_image.height();

    if (img_w > 0 && img_h > 0) {
        auto scale_w = win_w / img_w;
        auto scale_h = win_h / img_h;

        double x = 0;
        double y = 0;
        double w = win_w;
        double h = win_h;

        if (scale_w > scale_h) {
            w = scale_h * img_w;
            x = win_w / 2 - w / 2;
        }
        else {
            h = scale_w * img_h;
            y = win_h / 2 - h / 2;
        }

        painter->drawImage(QRectF(x, y, w, h), m_dicom_image);
    }
}

void Quick::drawRing(QPainter *painter, const Ring &ring)
{
    if (!ring.empty()) {
        for (int i = 0; i < ring.size(); i++) {
            painter->drawEllipse(QRectF(ring[i].x() - 3, ring[i].y() - 3, 6, 6));

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

    drawImage(painter);

    painter->setPen(QColor(0, 200, 0));
    painter->setBrush(QBrush(QColor(255, 0, 0)));

    painter->drawEllipse(m_current_point, 10, 10);

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
    m_current_point = event->posF();

    if (!m_current_ring.empty()) {
        update();
    }
        update();
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
