#ifndef DIAL_H
#define DIAL_H

#include <QAbstractSlider>
#include <QIcon>
#include <QRegion>
#include <QPainter>
//#include <pub/point3d.h>
#include <pub/hifutype.h>

#include "circulariconhelper.h"
#include "ringediconhelper.h"
#include "circularbutton.h"

/**
 * @class Dial
 * @brief The Dial class
 */
class Dial: public QAbstractSlider {

    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param[in] min The minimum
     * @param[in] max The maximum
     * @param[in] parent The parent widget
     */
    explicit Dial(int min, int max, QWidget *parent = 0);

    /**
     * @brief Constructor
     * @param[in] min The minimum
     * @param[in] max The maximum
     * @param[in] dft The default value
     * @param[in] parent The parent widget
     */
    explicit Dial(int min, int max, int dft, QWidget *parent = 0);

    /**
     * @brief Destructor
     */
    ~Dial();

    /**
     * @brief Size hint
     * @return The size hint
     */
    QSize sizeHint() const;

    /**
     * @brief Get default value
     * @return Set default value
     */
    int getDefaultValue() const;

    /**
     * @brief Set default value
     * @param[in] value The default value
     */
    void setDefaultValue(int value);

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
     * @brief Value to angle
     * @param[in] value The value
     * @return The radian
     */
    double value2Angle(double value) const;

    /**
     * @brief Reset ICON region
     * @param[in] size Current size
     */
    void resetIconRegion(const QSize &size);

    /**
     * @brief Update value
     * @param[in] point The cursor point
     */
    void updateValue(const QPointF &point);

    /**
     * @brief Draw panel
     * @param[in] painter The painter
     */
    virtual void drawPanel(QPainter &painter);

    /**
     * @brief Draw tracking
     * @param[in] painter The painter
     */
    virtual void drawTracking(QPainter &painter);

    /**
     * @brief Draw notch
     * @param[in] painter The painter
     */
    virtual void drawNotch(QPainter &painter);

    /**
     * @brief Draw switch
     * @param[in] painter The painter
     */
    virtual void drawSwitch(QPainter &painter);

    /**
     * @brief Draw indicator
     * @param[in] painter The painter
     */
    virtual void drawIndicator(QPainter &painter);

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

    /**
     * @brief paintEvent
     * @param event
     */
    virtual void paintEvent(QPaintEvent *event);

    /**
     * @brief resizeEvent
     * @param event
     */
    virtual void resizeEvent(QResizeEvent *event);

    /**
     * @brief mouseMoveEvent
     * @param event
     */
    virtual void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent
     * @param event
     */
    virtual void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    virtual void mouseReleaseEvent(QMouseEvent *event);

protected slots:

    /**
     * @brief increase
     */
    void increase();

    /**
     * @brief descrease
     */
    void descrease();

    /**
     * @brief setDefault
     */
    void setDefault();

    /**
     * @brief Update button state
     * @param[in] value Current value
     */
    void updateButtonState(int value);

protected:

    const static double K_INIT_ANGLE_DEG;
    const static double K_INIT_ANGLE;
    const static double K_RANGE_ANGLE_DEG;
    const static double K_RANGE_ANGLE;

    const static QColor K_DARK_COLOR;
    const static QColor K_BRIGHT_COLOR;

    CircularIconHelper m_panel_icon;
    RingedIconHelper m_switch_icon;
    IconHelper m_indicator_icon;

    CircularButton *m_add_btn;
    CircularButton *m_sub_btn;
    CircularButton *m_dft_btn;

    double m_indicator_radius;
    double m_tracking_radius;
    double m_notch_radius;
    double m_notch_value_radius;

    int m_dft_value;

    bool m_hover_switch;
    bool m_adjust;

};

#endif
