#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class MainWindow: public QWidget {

    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

protected slots:

    void on_create();

protected:

    QLineEdit *m_line_edit;
    QPushButton *m_create_btn;
    QPushButton *m_start_btn;
    QPushButton *m_quit_btn;

};
