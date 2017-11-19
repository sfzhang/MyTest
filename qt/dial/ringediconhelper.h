/**
 * @file The ringed icon resource
 * @author sfzhang
 * @date 2017-11-16
 */

#ifndef RINGEDICONHELPER_H
#define RINGEDICONHELPER_H

#include "iconhelper.h"
#include <QIcon>
#include <QSizeF>
#include <QPointF>
#include <cmath>

class RingedIconHelper: public IconHelper {

public:

    void setInnerRadius(double inner_radius)
    {
        m_inner_radius = inner_radius;
    }

    double getInnerRadius() const
    {
        return m_inner_radius;
    }

    void setOuterRadius(double outer_radius)
    {
        m_outer_radius = outer_radius;
    }

    double getOuterRadius() const
    {
        return m_outer_radius;
    }

    virtual bool contains(const QPointF &point) const
    {
        QPointF v = point - m_center;
        double d = v.x() * v.x() + v.y() * v.y();
        return ((d <= (std::pow(getOuterRadius() * m_scale, 2))) &&
                (d >= (std::pow(getInnerRadius() * m_scale, 2))));
    }

protected:

    double m_inner_radius;
    double m_outer_radius;

};

#endif
