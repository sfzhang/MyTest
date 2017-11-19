/**
 * @file The circular icon resource
 * @author sfzhang
 * @date 2017-11-16
 */

#ifndef CIRCULARICONHELPER_H
#define CIRCULARICONHELPER_H

#include "iconhelper.h"
#include <QIcon>
#include <QSizeF>
#include <QPointF>
#include <cmath>

class CircularIconHelper: public IconHelper {

public:

    void setRadius(double radius)
    {
        m_radius = radius;
    }

    double getRadius() const
    {
        return m_radius;
    }

    virtual bool contains(const QPointF &point) const
    {
        QPointF vec = point - m_center;
        double d = vec.x() * vec.x() + vec.y() * vec.y();
        return (d <= (std::pow(m_radius * m_scale, 2)));
    }

protected:

    double m_radius;

};

#endif
