#include "phasewidget.h"
#include "ui_phasewidget.h"
#include "phasedelegate.h"

PhaseWidget::PhaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhaseWidget),
    m_model(new PhaseModel)
{
    ui->setupUi(this);

    ui->m_phase_tv->setModel(m_model);
    ui->m_phase_tv->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->m_phase_tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_phase_tv->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_phase_tv->resizeColumnsToContents();

    auto delegate = new PhaseDelegate();
    ui->m_phase_tv->setItemDelegate(delegate);

    connect(ui->m_add_btn, &QPushButton::clicked, this, &PhaseWidget::add);
    connect(ui->m_delete_btn, &QPushButton::clicked, this, &PhaseWidget::remove);
    connect(ui->m_clear_btn, &QPushButton::clicked, this, &PhaseWidget::clear);
}

PhaseWidget::~PhaseWidget()
{
    delete ui;
}

void PhaseWidget::add()
{
    auto index = ui->m_phase_tv->currentIndex();
    if (index.isValid()) {
        ui->m_phase_tv->model()->insertRow(index.row());
        ui->m_phase_tv->selectRow(index.row());
    }
    else {
        ui->m_phase_tv->model()->insertRow(0);
        ui->m_phase_tv->selectRow(0);
    }
}

void PhaseWidget::remove()
{
    auto index = ui->m_phase_tv->currentIndex();
    if (index.isValid()) {
        int n = index.row();
        ui->m_phase_tv->model()->removeRow(n);

        if (n >= ui->m_phase_tv->model()->rowCount()) {
            n--;
        }

        if (n >= 0) {
            ui->m_phase_tv->selectRow(n);
        }
    }
}

void PhaseWidget::clear()
{
    ui->m_phase_tv->model()->removeRows(0, ui->m_phase_tv->model()->rowCount());
}
