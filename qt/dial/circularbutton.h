/**
 * @file Circular button
 *
 * @author sfzhang
 * @date 2017-11-20
 */

#ifndef CIRCULARBUTTON_H
#define CIRCULARBUTTON_H

#include "circulariconhelper.h"
#include <QIcon>
#include <QPointF>
#include <QPushButton>

class CircularButton: public QPushButton {

    Q_OBJECT

public:

    CircularButton(double radius, double length, const QIcon &icon = QIcon(),
                   const QString &text = QString(), QWidget *widget = nullptr);

    ~CircularButton();

    QSize sizeHint() const;

    QSize minimumSizeHint() const;

    double length() const
    {
        return m_length;
    }

protected:

    virtual bool hitButton(const QPoint &pos) const;

    virtual void paintEvent(QPaintEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void leaveEvent(QEvent *event);

protected:

    double m_radius;
    double m_length;

    bool m_hover;

};

#endif
