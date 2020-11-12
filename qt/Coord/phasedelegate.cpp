#include "phasedelegate.h"
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QLineEdit>
#include <QValidator>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

PhaseDelegate::PhaseDelegate(QObject *parent):
    QStyledItemDelegate(parent),
    m_phase_le(new QLineEdit)
{
    // phase
    auto val = new QDoubleValidator(-M_PI, M_PI, 4, m_phase_le);
    m_phase_le->setValidator(val);
}

PhaseDelegate::~PhaseDelegate()
{
    delete m_phase_le;
}

QWidget* PhaseDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    switch (index.column()) {
    case 0:
        m_phase_le->setParent(parent);
        return m_phase_le;
    default:
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void PhaseDelegate::destroyEditor(QWidget *editor, const QModelIndex &) const
{
    editor->hide();
}

void PhaseDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                         const QModelIndex &) const
{
    editor->setGeometry(option.rect);
    editor->show();
}

void PhaseDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column()) {
    case 0:
        model->setData(index, m_phase_le->text(), Qt::EditRole);
        break;
    default:
        QStyledItemDelegate::setModelData(editor, model, index);
        break;
    }
}

void PhaseDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto data = index.model()->data(index, Qt::EditRole);
    switch (index.column()) {
    case 0:
        m_phase_le->setText(data.toString());
        break;
    default:
        QStyledItemDelegate::setEditorData(editor, index);
    }
}
