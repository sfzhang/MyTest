#ifndef RINGNODE_H
#define RINGNODE_H

#include <QQuickItem>
#include <QVector>
#include <QPointF>

class RingNode: public QQuickItem {

    Q_OBJECT

    using Ring = QVector<QPointF>;

public:

    explicit RingNode(QQuickItem *parent = nullptr);

    QSGNode *updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *) override;

    virtual void mouseDoubleClickEvent(QMouseEvent *) override;

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void hoverMoveEvent(QHoverEvent *event) override;

protected:

    QPointF m_current_point;
    Ring m_current_ring;

};

#endif // RINGNODE_H
