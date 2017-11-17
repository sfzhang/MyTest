/**
 * @file The ringed icon resource
 * @author sfzhang
 * @date 2017-11-16
 */

#ifndef RINGEDICON_H
#define RINGEDICON_H

#include "icon.h"
#include <QIcon>
#include <QSizeF>
#include <QPointF>

class RingedIcon: public Icon {

public:

    RingedIcon(const QIcon &icon): Icon(icon) {}

    void setInnerRatio(double ratio)
    {
        m_inner_ratio = ratio;
    }

    double getInnerRatio() const
    {
        return m_inner_ratio;
    }

    double getInnerRadius() const
    {
        return qMin(m_size.width(), m_size.height()) / 2 * m_inner_ratio;
    }

    double getOuterRadius() const
    {
        return qMin(m_size.width(), m_size.height()) / 2 * (1 - m_inner_ratio);
    }

    virtual bool contains(const QPointF &point) const
    {
        QPointF delta = point - m_position;
        double d = delta.x() * delta.x() + delta.y() * delta.y();
        double inner_radius = getInnerRadius();
        double outer_radius = getOuterRadius();

        return ((d <= (outer_radius * outer_radius)) &&
                (d >= (inner_radius * inner_radius)));
    }

protected:

    double m_inner_ratio;

};

#endif
