/**
 * @file Quick widget
 */

#ifndef QUICK_H
#define QUICK_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QImage>

class Quick: public QQuickPaintedItem {

    Q_OBJECT

    using Ring = QVector<QPointF>;

public:

    explicit Quick(QQuickItem *parent = nullptr);

    virtual void paint(QPainter *painter) override;

    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void hoverMoveEvent(QHoverEvent *event) override;

    virtual void hoverEnterEvent(QHoverEvent *event) override;

    virtual void hoverLeaveEvent(QHoverEvent *event) override;

protected slots:

    void onWidthChanged();

    void onHeightChanged();

protected:

    void drawRing(QPainter *painter, const Ring &ring);

    void drawImage(QPainter *painter);

private:

    QPointF m_current_point;
    Ring m_current_ring;
    QVector<Ring> m_ring_list;

    QImage m_dicom_image;

};

#endif
