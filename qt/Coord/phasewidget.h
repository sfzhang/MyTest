#ifndef PHASEWIDGET_H
#define PHASEWIDGET_H

#include <QWidget>
#include "phasemodel.h"

namespace Ui {
class PhaseWidget;
}

class PhaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PhaseWidget(QWidget *parent = nullptr);
    ~PhaseWidget();


private slots:

    void add();

    void remove();

    void clear();

private:
    Ui::PhaseWidget *ui;

    PhaseModel *m_model;
};

#endif // PHASEWIDGET_H
