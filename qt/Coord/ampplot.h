#ifndef AMPPLOT_H
#define AMPPLOT_H

#include <qwt_plot.h>

class QwtPlotCurve;
class QwtPlotMarker;
class QwtPlotTextLabel;
class QwtPlotMagnifier;
class QwtPlotPanner;

class AmpPlot: public QwtPlot {

    Q_OBJECT

public:

    AmpPlot(QWidget *parent = nullptr);

    virtual ~AmpPlot() override;

    void setData();

protected slots:

    void showItem();

protected:

    void mousePressEvent(QMouseEvent *e) override;

    void mouseDoubleClickEvent(QMouseEvent *e) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    void wheelEvent(QWheelEvent *e) override;

protected:

    bool hit(int axis_id, const QPoint &pt);

    void resetAxisScale();

protected:

    int m_channel_count;

    QwtPlotCurve *m_voltage_curve; ///< Voltage curve
    QwtPlotCurve *m_current_curve; ///< Current curve
    QwtPlotMarker *m_marker; ///< The marker
    QwtPlotMagnifier *m_magnifier; ///< The magnifier
    QwtPlotPanner *m_panner; ///< The panner
    QwtPlotTextLabel *m_lbl; ///< The label

};

#endif // AMPPLOT_H
