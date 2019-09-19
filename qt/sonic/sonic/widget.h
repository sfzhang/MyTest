#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QTimer>

class MessageBox;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

protected:

    void paintEvent(QPaintEvent *) override;

    void render();

protected slots:

    void on_close(int r);

private:

    QImage m_image;
    QTimer m_timer;

    int32_t m_i;
    bool m_r;

    MessageBox *m_msg_box;

};

#endif // WIDGET_H
