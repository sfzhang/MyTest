#include "ampplot.h"
#include <QPolygon>
#include <QMouseEvent>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_textlabel.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>

AmpPlot::AmpPlot(QWidget *parent):
    QwtPlot(parent),
    m_channel_count(5),
    m_voltage_curve(new QwtPlotCurve(tr("Voltage"))),
    m_current_curve(new QwtPlotCurve(tr("Current"))),
    m_marker(new QwtPlotMarker),
    m_magnifier(nullptr),
    m_panner(nullptr),
    m_lbl(new QwtPlotTextLabel)
{
    setAutoReplot(false);
    setMouseTracking(true);

    setAxisTitle(QwtPlot::xBottom, "Channels");
    setAxisScale(QwtPlot::xBottom, 0, m_channel_count);
    setAxisAutoScale(QwtPlot::xBottom, false);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignCenter | Qt::AlignBottom);
    setAxisTitle(QwtPlot::yLeft, tr("V/V"));
    setAxisLabelAlignment(QwtPlot::yLeft, Qt::AlignLeft | Qt::AlignCenter);
    setAxisScale(QwtPlot::yLeft, 0, 24);
    setAxisAutoScale(QwtPlot::yLeft, false);
    setAxisTitle(QwtPlot::yRight, tr("I/A"));
    setAxisLabelAlignment(QwtPlot::yRight, Qt::AlignLeft | Qt::AlignCenter);
    setAxisScale(QwtPlot::yRight, 0, 2);
    setAxisAutoScale(QwtPlot::yRight, false);
    enableAxis(QwtPlot::yRight);

    m_voltage_curve->setPen(Qt::green, 2);
    m_voltage_curve->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, Qt::green, QPen(Qt::green), QSize(3, 3)));
    m_voltage_curve->attach(this);

    QPolygonF p1{QVector<QPointF>{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}};
    m_voltage_curve->setSamples(p1);

    m_current_curve->setPen(Qt::blue, 2);
    m_current_curve->setSymbol(new QwtSymbol(QwtSymbol::Rect, Qt::blue, QPen(Qt::blue), QSize(3, 3)));
    m_current_curve->attach(this);
    m_current_curve->setYAxis(QwtPlot::yRight);

    QPolygonF p2{QVector<QPointF>{{0, 0}, {1, 0}, {2, 0}, {3, 1}, {4, 2}}};
    m_current_curve->setSamples(p2);

    // Canvas
    setCanvas(new QwtPlotCanvas(this));
    canvas()->setMouseTracking(true);
    plotLayout()->setAlignCanvasToScale(QwtPlot::xBottom, false);
    plotLayout()->setAlignCanvasToScale(QwtPlot::yLeft, false);
    plotLayout()->setAlignCanvasToScale(QwtPlot::yRight, false);

    // Panner
    m_panner = new QwtPlotPanner(canvas());
    m_panner->setMouseButton(Qt::LeftButton);

    // Magnifier
    m_magnifier = new QwtPlotMagnifier(canvas());
    m_magnifier->setMouseButton(Qt::RightButton);

    // Marker
    m_marker->setLabelOrientation(Qt::Horizontal);
    m_marker->setLineStyle(QwtPlotMarker::VLine);
    m_marker->setLinePen(Qt::yellow, 2, Qt::DashLine);
    m_marker->attach(this);
    m_marker->hide();

    // Legend
    auto legend = new QwtLegend;
    legend->setDefaultItemMode(QwtLegendData::ReadOnly);
    insertLegend(legend, QwtPlot::RightLegend);

    // Label
    m_lbl->attach(this);
    setData();

    //connect(legend, &QwtLegend::checked, this, &AmpPlot::showItem);
}

AmpPlot::~AmpPlot()
{

}

void AmpPlot::setData()
{
    QString str = QString("Max V: %1\nMin V: %1\nMax I:%3\nMin I: %4")
                    .arg(m_voltage_curve->maxYValue(), 0, 'f', 1)
                    .arg(m_voltage_curve->minYValue(), 0, 'f', 1)
                    .arg(m_current_curve->maxYValue(), 0, 'f', 1)
                    .arg(m_current_curve->minYValue(), 0, 'f', 1);

    QwtText text(str);
    text.setColor(Qt::red);
    text.setRenderFlags(Qt::AlignLeft | Qt::AlignTop);
    m_lbl->setText(text);
}

void AmpPlot::showItem()
{
    auto item_list = itemList(QwtPlotItem::Rtti_PlotCurve);
    for (auto &item: item_list) {
        qDebug() << item->title().text();
        if (item->title().text() == QString("Current")) {
            item->setVisible(!item->isVisible());
        }
    }
    replot();
}

bool AmpPlot::hit(int axis_id, const QPoint &pt)
{
    int w = width() / 3;
    int h = height() / 3;

    auto axis = axisWidget(axis_id);
    if (axis) {
        QPolygon poly(4);
        switch (axis_id) {
        case QwtPlot::yLeft:
            poly.setPoint(0, axis->x() + axis->width(), axis->y());
            poly.setPoint(1, axis->x() + axis->width() + w, axis->y());
            poly.setPoint(2, axis->x() + axis->width() + w, axis->y() + axis->height() - h);
            poly.setPoint(3, axis->x() + axis->width(), axis->y() + axis->height());
            break;
        case QwtPlot::yRight:
            poly.setPoint(0, axis->x() - w, axis->y());
            poly.setPoint(1, axis->x(), axis->y());
            poly.setPoint(2, axis->x(), axis->y() + axis->height());
            poly.setPoint(3, axis->x() - w, axis->y() + axis->height() - h);
            break;
        case QwtPlot::xBottom:
            poly.setPoint(0, axis->x(), axis->y());
            poly.setPoint(1, axis->x() + w, axis->y() - h);
            poly.setPoint(2, axis->x() + axis->width() - w , axis->y() - h);
            poly.setPoint(3, axis->x() + axis->width(), axis->y());
            break;
        }

        if (poly.containsPoint(pt, Qt::OddEvenFill)) {
            return true;
        }
    }
    return false;
}

void AmpPlot::resetAxisScale()
{
    setAxisScale(QwtPlot::xBottom, 0, m_channel_count);
    setAxisScale(QwtPlot::yLeft, m_voltage_curve->minYValue() - 2, m_voltage_curve->maxYValue() + 3);
    setAxisScale(QwtPlot::yRight, m_current_curve->minYValue() - 1, m_current_curve->maxYValue() + 2);
    replot();
}

void AmpPlot::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        if (hit(QwtPlot::yLeft, e->pos())) {
            m_magnifier->setAxisEnabled(QwtPlot::yLeft, true);
            m_magnifier->setAxisEnabled(QwtPlot::yRight, false);
            m_magnifier->setAxisEnabled(QwtPlot::xBottom, false);
        }
        else if (hit(QwtPlot::yRight, e->pos())) {
            m_magnifier->setAxisEnabled(QwtPlot::yLeft, false);
            m_magnifier->setAxisEnabled(QwtPlot::yRight, true);
            m_magnifier->setAxisEnabled(QwtPlot::xBottom, false);
        }
        else if (hit(QwtPlot::xBottom, e->pos())) {
            m_magnifier->setAxisEnabled(QwtPlot::yLeft, false);
            m_magnifier->setAxisEnabled(QwtPlot::yRight, false);
            m_magnifier->setAxisEnabled(QwtPlot::xBottom, true);
        }
        else {
            m_magnifier->setAxisEnabled(QwtPlot::yLeft, true);
            m_magnifier->setAxisEnabled(QwtPlot::yRight, true);
            m_magnifier->setAxisEnabled(QwtPlot::xBottom, true);
        }
    }
    else if (e->button() == Qt::LeftButton) {
        m_panner->setAxisEnabled(QwtPlot::yLeft, true);
        m_panner->setAxisEnabled(QwtPlot::yRight, true);
        m_panner->setAxisEnabled(QwtPlot::xBottom, true);
    }

    QwtPlot::mousePressEvent(e);
}

void AmpPlot::mouseDoubleClickEvent(QMouseEvent *e)
{
    QwtPlot::mouseDoubleClickEvent(e);
    resetAxisScale();
}

void AmpPlot::mouseMoveEvent(QMouseEvent *e)
{
    bool visiable = false;
    if (m_voltage_curve->isVisible() && m_current_curve->isVisible()) {
        auto scale_map = canvasMap(QwtPlot::xBottom);
        int channel = static_cast<int>(scale_map.invTransform(e->pos().x() - canvas()->geometry().left()));
        double center = (scale_map.s1() + scale_map.s2()) / 2;
        if ((channel >= 0) && (channel < m_channel_count)) {
            QString label;
            if (m_voltage_curve->isVisible()) {
                label = QString("V: %1").arg(m_voltage_curve->sample(channel).y(), 0, 'f', 1);
            }
            if (m_current_curve->isVisible()) {
                if (!label.isEmpty()) {
                    label += "\n";
                }
                label += QString("I: %1").arg(m_current_curve->sample(channel).y(), 0, 'f', 1);
            }

            m_marker->setLabel(label);
            m_marker->setXValue(channel);

            if (channel > center) {
                m_marker->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
            }
            else {
                m_marker->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
            }
            visiable = true;
        }
    }

    m_marker->setVisible(visiable);
    replot();

    QwtPlot::mouseMoveEvent(e);
}

void AmpPlot::wheelEvent(QWheelEvent *e)
{
    if (hit(QwtPlot::yLeft, e->pos())) {
        m_magnifier->setAxisEnabled(QwtPlot::yLeft, true);
        m_magnifier->setAxisEnabled(QwtPlot::yRight, false);
        m_magnifier->setAxisEnabled(QwtPlot::xBottom, false);
    }
    else if (hit(QwtPlot::yRight, e->pos())) {
        m_magnifier->setAxisEnabled(QwtPlot::yLeft, false);
        m_magnifier->setAxisEnabled(QwtPlot::yRight, true);
        m_magnifier->setAxisEnabled(QwtPlot::xBottom, false);
    }
    else if (hit(QwtPlot::xBottom, e->pos())) {
        m_magnifier->setAxisEnabled(QwtPlot::yLeft, false);
        m_magnifier->setAxisEnabled(QwtPlot::yRight, false);
        m_magnifier->setAxisEnabled(QwtPlot::xBottom, true);
    }
    else {
        m_magnifier->setAxisEnabled(QwtPlot::yLeft, true);
        m_magnifier->setAxisEnabled(QwtPlot::yRight, true);
        m_magnifier->setAxisEnabled(QwtPlot::xBottom, true);
    }

    QwtPlot::wheelEvent(e);
}
