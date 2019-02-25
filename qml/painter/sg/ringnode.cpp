#include "ringnode.h"
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

RingNode::RingNode(QQuickItem *parent):
    QQuickItem(parent)
{
    setAntialiasing(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemHasContents, true);
}

void RingNode::mousePressEvent(QMouseEvent *event)
{
    m_current_ring.push_back(event->localPos());
    m_current_point = event->localPos();
    update();
}

void RingNode::mouseDoubleClickEvent(QMouseEvent *)
{
    m_current_ring.clear();
    update();
}

void RingNode::hoverMoveEvent(QHoverEvent *event)
{
    m_current_point = event->posF();

    if (!m_current_ring.empty()) {
        update();
    }
}

QSGNode *RingNode::updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if (!old_node) {
        node = new QSGGeometryNode();
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_current_ring.size() + 1);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        auto material = new QSGFlatColorMaterial();
        material->setColor(QColor(255, 0, 0));
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsGeometry);
    }
    else {
        node = static_cast<QSGGeometryNode *>(old_node);
        geometry = node->geometry();
        geometry->allocate(m_current_ring.size() + 1);
    }

    auto *vertices = geometry->vertexDataAsPoint2D();
    for (int i = 0; i < m_current_ring.size(); ++i) {
        vertices[i].set(static_cast<float>(m_current_ring[i].x()), static_cast<float>(m_current_ring[i].y()));
    }

    vertices[m_current_ring.size()].set(static_cast<float>(m_current_point.x()),
                                        static_cast<float>(m_current_point.y()));
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}
