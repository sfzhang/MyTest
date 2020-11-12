#include "widget.h"
#include "ui_widget.h"
#include "coorddelegate.h"
#include <QPushButton>
#include <QTableWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_delegate(new CoordDelegate),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->m_coord_tw->setColumnCount(6);
    ui->m_coord_tw->setItemDelegate(m_delegate);
    ui->m_coord_tw->setHorizontalHeaderLabels({"FUS Coord.(x1,y1,z1)(...)(mm)", "Spot Type", "Vol(V)", "Freq.(HZ)",
                                               "Heat T.(ms)", "Cool T.(ms)"});
    ui->m_coord_tw->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->m_coord_tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_coord_tw->resizeColumnsToContents();

    connect(ui->m_add_btn, &QPushButton::clicked, this, &Widget::add_btn_clicked);
    connect(ui->m_delete_btn, &QPushButton::clicked, this, &Widget::delete_btn_clicked);
    connect(ui->m_clear_btn, &QPushButton::clicked, this, &Widget::clear_btn_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::add_btn_clicked()
{
    auto n = ui->m_coord_tw->currentRow() + 1;

    if ((n < 0) || (n > ui->m_coord_tw->rowCount())) {
        n = ui->m_coord_tw->rowCount();
    }

    ui->m_coord_tw->insertRow(n);

    auto item = new QTableWidgetItem("(0,0,0)");
    item->setTextAlignment(Qt::AlignCenter);
    ui->m_coord_tw->setItem(n, 0, item);

    item = new QTableWidgetItem(m_delegate->defaultSpotType());
    item->setTextAlignment(Qt::AlignCenter);
    ui->m_coord_tw->setItem(n, 1, item);

    item = new QTableWidgetItem(m_delegate->defaultVoltage());
    item->setTextAlignment(Qt::AlignCenter);
    ui->m_coord_tw->setItem(n, 2, item);

    item = new QTableWidgetItem(m_delegate->defaultFreq());
    item->setTextAlignment(Qt::AlignCenter);
    ui->m_coord_tw->setItem(n, 3, item);

    item = new QTableWidgetItem(m_delegate->defaultHeatTime());
    item->setTextAlignment(Qt::AlignCenter);
    ui->m_coord_tw->setItem(n, 4, item);

    item = new QTableWidgetItem(m_delegate->defaultCoolTime());
    item->setTextAlignment(Qt::AlignCenter);
    ui->m_coord_tw->setItem(n, 5, item);

    ui->m_coord_tw->selectRow(n);
}

void Widget::delete_btn_clicked()
{
    ui->m_coord_tw->removeRow(ui->m_coord_tw->currentRow());
}

void Widget::clear_btn_clicked()
{
    ui->m_coord_tw->model()->removeRows(0, ui->m_coord_tw->rowCount());
    ui->m_coord_tw->clearContents();
}
