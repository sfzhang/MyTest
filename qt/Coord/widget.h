#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "coorddelegate.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void add_btn_clicked();

    void delete_btn_clicked();

    void clear_btn_clicked();

private:

    CoordDelegate *m_delegate;
    Ui::Widget *ui;

};

#endif // WIDGET_H
