/**
 * @file The circular icon resource
 * @author sfzhang
 * @date 2017-11-16
 */

#ifndef CIRCULARICON_H
#define CIRCULARICON_H

#include "icon.h"
#include <QIcon>
#include <QSizeF>
#include <QPointF>

class CircularIcon: public Icon {

public:

    CircularIcon(const QIcon &icon): Icon(icon) {}

    double getRadius() const
    {
        return qMin(m_size.width(), m_size.height()) / 2;
    }

    virtual bool contains(const QPointF &point) const
    {
        QPointF delta = point - m_position;
        double d = delta.x() * delta.x() + delta.y() * delta.y();
        double radius = getRadius();
        return (d <= (radius * radius));
    }

};

#endif
