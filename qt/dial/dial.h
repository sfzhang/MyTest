#ifndef DIAL_H
#define DIAL_H

#include <QAbstractSlider>
#include <QIcon>
#include <QRegion>
#include <pub/point3d.h>
#include <pub/hifutype.h>

#include "circulariconhelper.h"
#include "ringediconhelper.h"
#include "circularbutton.h"

class Dial: public QAbstractSlider {

    Q_OBJECT

public:

    explicit Dial(int min, int max, QWidget *parent = 0);

    explicit Dial(int min, int max, int dft, QWidget *parent = 0);

    ~Dial();

    QSize sizeHint() const;

    int getDefaultValue() const;

    void setDefaultValue(int value);

    void showNotchValue(bool enable);

protected:

    void initialize();

    double getFontSize(const QString &text, double scale) const;

    double value2Angle(double value) const;

    void resetIconRegion(const QSize &size);

    void updateIndicatorCenter();

    void updateValue(const QPointF &point);

    virtual void paintEvent(QPaintEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

protected slots:

    void increase();

    void descrease();

    void setDefault();

    void updateButtonState(int value);

private:

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

    bool m_show_dft_value;
    bool m_show_notch_value;

    bool m_hover_switch;
    bool m_adjust;

};

#endif
