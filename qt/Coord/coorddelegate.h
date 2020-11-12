#ifndef COORDDELEGATE_H
#define COORDDELEGATE_H

#include <QStyledItemDelegate>
class QComboBox;
class QLineEdit;
class QDoubleValidator;

class CoordDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    CoordDelegate(QObject *parent = nullptr);

    ~CoordDelegate() override;

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const override;

    virtual void destroyEditor(QWidget *editor, const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QString defaultSpotType() const;

    QString defaultVoltage() const;

    QString defaultFreq() const;

    QString defaultHeatTime() const;

    QString defaultCoolTime() const;

private slots:

    void commitAndCloseEditor();

private:

    mutable QLineEdit *m_coord_le;
    mutable QComboBox *m_spot_type_cbb;
    mutable QLineEdit *m_voltage_le;
    mutable QComboBox *m_freq_cbb;
    mutable QLineEdit *m_heat_time_le;
    mutable QLineEdit *m_cool_time_le;
    mutable QDoubleValidator *m_voltage_val;

};

#endif // COORDDELEGATE_H
