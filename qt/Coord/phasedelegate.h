#ifndef PHASEDELEGATE_H
#define PHASEDELEGATE_H

#include <QLineEdit>
#include <QStyledItemDelegate>

/**
 * @brief The PhaseDelegate class
 */
class PhaseDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param[in] parent The parent
     */
    PhaseDelegate(QObject *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~PhaseDelegate() override;

    /**
     * @brief Reimplement createEditor
     * @param[in] parent The parent widget
     * @param[in] option The style option view item
     * @param[in] index The current index
     * @return The creatod editor
     */
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

    /**
     * @brief Reimplement setEditorData
     * @param[in] editor The editor widget
     * @param[in] index The current index
     */
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    /**
     * @brief Reimplement setModelData
     * @param[in] editor The editor widget
     * @param[in] model The model
     * @param[in] index The current index
     */
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const override;

    /**
     * @brief Reimplement destroyEditor
     * @param[in] editor The editor widget
     * @param[in] index The current index
     */
    virtual void destroyEditor(QWidget *editor, const QModelIndex &index) const override;

    /**
     * @brief Reimplement updateEditorGeometry
     * @param[in] editor The editor widget
     * @param[in] option The style option
     * @param[in] index The current index
     */
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const override;

private:

    mutable QLineEdit *m_phase_le;      ///< The phase
};

#endif // PHASEDELEGATE_H
