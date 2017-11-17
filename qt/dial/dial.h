#ifndef DIAL_H
#define DIAL_H

#include <QDial>
#include <QIcon>
#include <QRegion>

class Dial: public QDial {

    Q_OBJECT

public:

    explicit Dial(QWidget *parent = 0);

    ~Dial();

protected:

    void resetIconRegion(const QSize &size);

    virtual void paintEvent(QPaintEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

private:

    QIcon *m_panel;
    QIcon *m_switch;
    QIcon *m_cursor;

    int m_x;
    int m_y;
    int m_length;

    bool m_adjust;
    double m_value;
    double m_min;
    double m_max;
    double m_prev_angle;
    double m_prev_value;

};

#endif
