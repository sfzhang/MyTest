/**
 * @file Simple dial
 *
 * @author sfzhang
 * @date 2017-11-21
 */

#ifndef SIMPLEDIAL_H
#define SIMPLEDIAL_H

#include "dial.h"

#include <QIcon>
#include <QRegion>
#include <QPainter>
#include <pub/point3d.h>
#include <pub/hifutype.h>

/**
 * @class SimpleDial
 * @brief The SimpleDial class without notch value
 */
class SimpleDial: public Dial {

    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param[in] min The minimum
     * @param[in] max The maximum
     * @param[in] parent The parent widget
     */
    explicit SimpleDial(int min, int max, QWidget *parent = 0);

    /**
     * @brief Constructor
     * @param[in] min The minimum
     * @param[in] max The maximum
     * @param[in] rec The recommend value
     * @param[in] parent The parent widget
     */
    explicit SimpleDial(int min, int max, int rec, QWidget *parent = 0);

    /**
     * @brief Get recommend value
     * @return Set recommend value
     */
    int getRecommendValue() const
    {
        return getDefaultValue();
    }

    /**
     * @brief Set recommend value
     * @param[in] value The recommend value
     */
    void setRecommendValue(int value)
    {
        setDefaultValue(value);
    }

protected:

    /**
     * @brief initialize
     */
    void initialize();

    /**
     * @brief Get font size
     * @param[in] text The text
     * @param[in] scale The scale
     * @return The font size
     */
    virtual double getFontSize(const QString &text, double scale) const;

    /**
     * @brief Draw notch
     * @param[in] painter The painter
     */
    virtual void drawNotch(QPainter &painter);

    /**
     * @brief Draw value
     * @param[in] angle The angle
     */
    virtual void drawValue(QPainter &painter);

    /**
     * @brief Draw notch value
     * @param[in] angle The angle
     */
    virtual void drawNotchValue(QPainter &painter);

protected:

    const static QColor K_REC_COLOR;

};

#endif
