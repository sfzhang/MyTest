#include <QApplication>  
#include <QImage>
#include <QWidget>
#include <QPoint>
#include <QPainter>

#ifndef WIDGET_H
#define WIDGET_H

class Widget: public QWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr):
        QWidget(parent)
    {
    }

    ~Widget() {}


    void setImage(const QImage &image)
    {
        m_image = image;
        update();
    }

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.drawImage(QPoint(0, 0), m_image);
    }

protected:

    QImage m_image;

};

#endif
