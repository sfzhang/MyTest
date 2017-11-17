/**
 * @file The icon resource
 * @author sfzhang
 * @date 2017-11-16
 */

#ifndef ICON_H
#define ICON_H

#include <QIcon>
#include <QSizeF>
#include <QPointF>

class Icon {

public:

    Icon(const QIcon &icon): m_icon(icon) {}

    const QIcon &getIcon() const
    {
        return m_icon;
    }

    void setSize(const QSizeF &size)
    {
        m_size = size;
    }

    const QSizeF &getSize() const
    {
        return m_size;
    }

    void setPosition(const QPointF &position)
    {
        m_position = position;
    }

    const QPointF &getPosition() const
    {
        return m_position;
    }

    QPointF center() const
    {
        QRectF rect(m_position, m_size);
        return rect.center();
    }

    virtual bool contains(const QPointF &point) const
    {
        QRectF rect(m_position, m_size);
        return rect.contains(point);
    }

protected:

    QIcon m_icon;
    QSizeF m_size;
    QPointF m_position;

};

#endif
