#include <QApplication>
#include <QHash>
#include <QString>
#include <QLabel>
#include <QThreadStorage>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *label = new QLabel();

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "1");
        db.setHostName("192.168.1.15");
        db.setDatabaseName("sd_hifu");
        db.setUserName("fus");
        db.setPassword("fus");
        if (!db.open()) {
            qDebug() << "open() failed";
            return -1;
        }
        db.close();
    }

    if (QSqlDatabase::database("1").isOpen()) {
        label->setText("opened");
    }

    label->show();
    return app.exec();
}
