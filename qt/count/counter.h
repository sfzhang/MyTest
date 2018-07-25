#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter: public QObject {

    Q_OBJECT

    int m_value;

public:
    int value() const { return m_value; }

public slots:
    void setValue(int val);

signals:
    void valueChanged(int value);
    int initialized(double v);

};

#endif
