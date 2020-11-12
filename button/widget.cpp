#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->m_btn->setEnabled(true);
}

Widget::~Widget()
{
    delete ui;
}
