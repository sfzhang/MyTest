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

/**
 * @class CircularButton
 * @brief The CircularButton class
 */
class CircularButton: public QPushButton {

    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param[in] radius The radius of circle, which must not be larger than
     *                   (length / 2)
     * @param[in] length The length of circular icon
     * @param[in] icon The circular icon
     * @param[in] text The text
     * @param[in] parent The parent widget
     */
    CircularButton(double radius, double length, const QIcon &icon,
                   const QString &text = QString(), QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~CircularButton();

    /**
     * @brief Size hint
     * @return Size hint
     */
    QSize sizeHint() const;

    /**
     * @brief Minimum size hint
     * @return Minimum size hint
     */
    QSize minimumSizeHint() const;

    /**
     * @brief Get the icon length
     * @return The icon length
     */
    double length() const
    {
        return m_length;
    }

protected:

    /**
     * @brief Get current button state for painting
     * @param[out] mode The ICON mode
     * @param[out] state The ICON state
     */
    void getStatus(QIcon::Mode &mode, QIcon::State &state) const;

    /**
     * @brief Get ICON geometry
     * @param[out] x The x position
     * @param[out] y The y position
     * @param[out] length The length
     */
    void getGeometry(double &x, double &y, double &length) const;

    /**
     * @brief Check if hit button
     * @param[in] pos The current position
     * @return True if hit, otherwise false
     */
    virtual bool hitButton(const QPoint &pos) const;

    /**
     * @brief paintEvent
     * @param event
     */
    virtual void paintEvent(QPaintEvent *event);

    /**
     * @brief mouseMoveEvent
     * @param event
     */
    virtual void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief leaveEvent
     * @param event
     */
    virtual void leaveEvent(QEvent *event);

protected:

    double m_radius;
    double m_length;

    bool m_hover;

};

#endif
