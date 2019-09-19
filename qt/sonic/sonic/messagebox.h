#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QPoint>
#include <QMessageBox>
#include <QMap>
#include <QPointer>

namespace Ui {
class MessageBox;
}

class MessageBox : public QDialog
{
    Q_OBJECT

public:

    MessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
               QMessageBox::StandardButtons buttons, QWidget *parent = nullptr);

    ~MessageBox() override;

    void disableClose(bool disabled = true);

    void setIcon(QMessageBox::Icon icon);

    QMessageBox::Icon icon() const;

    void setTitle(const QString &title);

    QString title() const;

    void setText(const QString &text);

    QString text() const;

    QPushButton* addButton(QMessageBox::StandardButton button);

    QPushButton* addButton(const QString &text);

    QCheckBox* setCheckBox(const QString &text);

    QCheckBox* checkBox() const;

    bool isChecked() const;

    QPushButton* clickedButton() const;

    QMessageBox::StandardButton standarClickedButton() const;

    static QMessageBox::StandardButton information(const QString &title, const QString &text,
                                                   QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QWidget *parent = nullptr);

    static QMessageBox::StandardButton question(const QString &title, const QString &text,
                                                QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                                                QWidget *parent = nullptr);

    static QMessageBox::StandardButton warning(const QString &title, const QString &text,
                                               QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                               QWidget *parent = nullptr);

    static QMessageBox::StandardButton critical(const QString &title, const QString &text,
                                                QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                QWidget *parent = nullptr);

protected:

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;

    void addStdButtons(QMessageBox::StandardButtons buttons);

    void relayout();

    static QMessageBox::StandardButton showMessageBox(QWidget *parent, QMessageBox::Icon icon,
                                                      const QString &title, const QString &text,
                                                      QMessageBox::StandardButtons buttons);

private:

    QPushButton *addBtnImpl(const QString &text, QMessageBox::StandardButton button);

    void on_close_btn_clicked();

    void on_btn_clicked();

private:

    static QMap<QMessageBox::StandardButton, QString> s_std_btn_text;

    Ui::MessageBox *ui;

    QMessageBox::StandardButtons m_std_btns;
    QMap<QString, QPair<QPushButton*, QMessageBox::StandardButton>> m_btns_map;
    QString m_clicked_btn_text;

    QVector<QString> m_btns_text;

    QMessageBox::Icon m_icon;

    double m_display_ratio;
    QPoint m_orig_pos;
    QPoint m_prev_point;
    bool m_move_widget;

};

#endif // MESSAGEBOX_H
