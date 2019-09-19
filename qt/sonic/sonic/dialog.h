#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPoint>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

protected:

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::Dialog *ui;

    QPoint m_prev_point;
    QPoint m_orig_point;
    bool m_move_widget;

};

#endif // DIALOG_H
