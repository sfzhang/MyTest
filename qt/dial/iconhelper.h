/**
 * @file The icon resource
 * @author sfzhang
 * @date 2017-11-16
 */

#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QIcon>
#include <QSizeF>
#include <QPointF>
#include <QPixmap>
#include <cmath>

class IconHelper {

public:

    IconHelper(): m_icon(nullptr), m_scale(1) {}

    ~IconHelper()
    {
        if (m_icon) {
            delete m_icon;
        }
    }

    void setIcon(QIcon *icon)
    {
        m_icon = icon;
    }

    QIcon *getIcon() const
    {
        return m_icon;
    }

    QPixmap getPixmap(QIcon::Mode mode = QIcon::Normal,
                      QIcon::State state = QIcon::Off) const
    {
        return m_icon->pixmap((m_size * m_scale).toSize(), mode, state);
    }

    void setSize(const QSizeF &size)
    {
        m_size = size;
    }

    QSizeF getSize() const
    {
        return m_size;
    }

    void setCenter(double x, double y)
    {
        setCenter(QPointF(x, y));
    }

    void setCenter(const QPointF &center)
    {
        m_center = center;
    }

    const QPointF &getCenter() const
    {
        return m_center;
    }

    QPointF getPosition() const
    {
        return QPointF(m_center.x() - m_size.width() * m_scale / 2,
                       m_center.y() - m_size.height() * m_scale / 2);
    }

    void setScale(double scale)
    {
        m_scale = scale;
    }

    double getScale() const
    {
        return m_scale;
    }

    virtual double angle(const QPointF &point) const
    {
        QPointF vec = point - m_center;
        return std::atan2(vec.y(), vec.x());
    }

    virtual bool contains(const QPointF &point) const
    {
        QRectF rect((m_center.x() + m_size.width() * m_scale / 2),
                    (m_center.y() + m_size.height() * m_scale / 2),
                    (m_size.width() * m_scale),
                    (m_size.height() * m_scale));
        return rect.contains(point);
    }

protected:

    QIcon *m_icon;
    QSizeF m_size;
    QPointF m_center;

    double m_scale;

};

#endif
