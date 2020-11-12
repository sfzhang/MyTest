#include "phasemodel.h"

PhaseModel::PhaseModel(QObject *parent):
    QAbstractTableModel(parent)
{
    m_data << 1 << 2;
}

int PhaseModel::rowCount(const QModelIndex &) const
{
    return m_data.size();
}

int PhaseModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant PhaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole == role){
        if (Qt::Vertical == orientation) {
            return section + 1;
        }
        else {
            switch (section) {
            case 0:
                return QString(tr("Phase"));
            }
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant PhaseModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignCenter);
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.row() >= 0 && (index.row() < m_data.size())) {
            return QVariant(m_data[index.row()]);
        }
    }

    return QVariant();
}

bool PhaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (Qt::EditRole == role) {
        if ((index.row() >= 0) && (index.row() < m_data.size()) ) {
            m_data[index.row()] = value.toDouble();
            return true;
        }
        else {
            return false;
        }
    }
    return QAbstractTableModel::setData(index, value, role);
}

Qt::ItemFlags PhaseModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool PhaseModel::insertRows(int row, int count, const QModelIndex &)
{
    if ((row < 0) || ((row > m_data.size()) || (count < 0))) {
        return false;
    }

    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; i++) {
        m_data.insert(i + row, 0);
    }
    endInsertRows();
    return true;
}

bool PhaseModel::removeRows(int row, int count, const QModelIndex &)
{
    if ((row < 0) || ((row + count - 1) >= m_data.size()) || ((count < 0))) {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    while (count > 0) {
        m_data.removeAt(row);
        count--;
    }
    endRemoveRows();

    return true;
}
