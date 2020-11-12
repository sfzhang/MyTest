#include "coorddelegate.h"
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QComboBox>
#include <QLineEdit>
#include <QValidator>
#include <QRegExp>

CoordDelegate::CoordDelegate(QObject *parent):
    QStyledItemDelegate(parent),
    m_coord_le(new QLineEdit),
    m_spot_type_cbb(new QComboBox),
    m_voltage_le(new QLineEdit),
    m_freq_cbb(new QComboBox),
    m_heat_time_le(new QLineEdit),
    m_cool_time_le(new QLineEdit),
    m_voltage_val(new QDoubleValidator)
{
    // match: (x1,y1,z1)(x2,y2,z2)...
    QRegExp rx(R"(( *\( *-?[0-9]+ *, *-?[0-9]+ *, *-?[0-9]+ *\) *)+)");
    m_coord_le->setValidator(new QRegExpValidator(rx));

    m_spot_type_cbb->addItems({"Normal", "Large"});
    m_voltage_val->setRange(0.1, 25, 1);
    m_voltage_le->setValidator(m_voltage_val);
    m_freq_cbb->addItems({"1360000", "1100000"});
    m_heat_time_le->setValidator(new QIntValidator(1, 5 * 60 * 1000));
    m_cool_time_le->setValidator(new QIntValidator(1, 5 * 60 * 1000));
}

CoordDelegate::~CoordDelegate()
{
    delete m_spot_type_cbb;
    delete m_voltage_le;
    delete m_freq_cbb;
    delete m_heat_time_le;
    delete m_cool_time_le;
}

QString CoordDelegate::defaultSpotType() const
{
    return m_spot_type_cbb->itemText(0);
}

QString CoordDelegate::defaultVoltage() const
{
    return "14";
}

QString CoordDelegate::defaultFreq() const
{
    return m_freq_cbb->itemText(0);
}

QString CoordDelegate::defaultHeatTime() const
{
    return "16000";
}

QString CoordDelegate::defaultCoolTime() const
{
    return "320000";
}

QWidget* CoordDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    switch (index.column()) {
    case 0:
        m_coord_le->setParent(parent);
        return m_coord_le;
    case 1:
        m_spot_type_cbb->setParent(parent);
        return m_spot_type_cbb;
    case 2:
        m_voltage_le->setParent(parent);
        return m_voltage_le;
    case 3:
        m_freq_cbb->setParent(parent);
        return m_freq_cbb;
    case 4:
        m_heat_time_le->setParent(parent);
        return m_heat_time_le;
    case 5:
        m_cool_time_le->setParent(parent);
        return m_cool_time_le;
    default:
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void CoordDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    editor->hide();
}

void CoordDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    editor->show();
}

void CoordDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column()) {
    case 0:
        model->setData(index, m_coord_le->text(), Qt::EditRole);
        break;
    case 1:
        model->setData(index, m_spot_type_cbb->currentText(), Qt::EditRole);
        break;
    case 2:
        model->setData(index, m_voltage_le->text(), Qt::EditRole);
        break;
    case 3: {
        model->setData(index, m_freq_cbb->currentText(), Qt::EditRole);
        auto voltage_index = index.siblingAtColumn(index.column() - 1);
        auto voltage = model->data(voltage_index).toInt();
        auto max_voltage = 12;
        if (voltage > max_voltage) {
            model->setData(voltage_index, max_voltage);
        }
        m_voltage_val->setTop(max_voltage);
        break;
    }
    case 4:
        model->setData(index, m_heat_time_le->text(), Qt::EditRole);
        break;
    case 5:
        model->setData(index, m_cool_time_le->text(), Qt::EditRole);
        break;
    default:
        QStyledItemDelegate::setModelData(editor, model, index);
        break;
    }
}

void CoordDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto data = index.model()->data(index, Qt::EditRole);
    switch (index.column()) {
    case 0:
        m_coord_le->setText(data.toString());
        break;
    case 1:
        m_spot_type_cbb->setCurrentText(data.toString());
        break;
    case 2:
        m_voltage_le->setText(data.toString());
        break;
    case 3:
        m_freq_cbb->setCurrentText(data.toString());
        break;
    case 4:
        m_heat_time_le->setText(data.toString());
        break;
    case 5:
        m_cool_time_le->setText(data.toString());
        break;
    default:
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void CoordDelegate::commitAndCloseEditor()
{

}

