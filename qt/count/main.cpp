#include <QCoreApplication>
#include "counter.h"
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QDir>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFileInfo>
#include <QFile>

using namespace std;

typedef boost::property_tree::ptree tptree;

template<typename T>
inline bool get(const tptree &ptree, const std::string &path, T &value)
{
    if (boost::optional<T> ret = ptree.get_optional<T>(path)) {
        value = *ret;
        return true;
    }

    return false;
}

inline bool get(const tptree &ptree, const std::string &path, QString &value)
{
    if (auto v = ptree.get_optional<std::string>(path)) {
        value = QString::fromStdString(*v);
        return true;
    }

    return false;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << QFile::exists("/tmp") << endl;
    qDebug() << QFile::remove("./ss") << endl;

    QFileInfo fi("/tmp/abc/def");
    qDebug() << fi.baseName() << endl;

    //QDir dir("./main.cpp");
    QDir dir("/home/fus/Git/MyTest/qt/count/main.cpp");
    if (dir.exists()) {
        qDebug() << "exist" << endl;
    }
    else {
        qDebug() << "not exist" << endl;
    }

    dir = QDir("/home/fus/Git/MyTest/qt/count/");
    if (dir.exists("b")) {
        qDebug() << "exist b" << endl;

        if (dir.rmdir("b")) {
            qDebug() << "remove b success" << endl;
        }
        else {
            qDebug() << "remove b failed" << endl;
        }
    }
    else {
        qDebug() << "not exist b" << endl;
    }

    if (dir.remove("a.tmp")) {
        qDebug() << "remove a.tmp success" << endl;
    }
    else {
        qDebug() << "remove a.tmp failed" << endl;
    }

    dir = QDir("/home/fus/Git/MyTest/qt/count/a.tmp/");
    if (dir.removeRecursively()) {
        qDebug() << "remove a.tmp recursively success" << endl;
    }
    else {
        qDebug() << "remove a.tmp recursively failed" << endl;
    }

    return 0;

    QDir dir2;
    qDebug() << dir.mkpath("/home/fus/Git/MyTest/qt/count/main.cpp");
    qDebug() << dir.mkpath("/home/fus/Git/MyTest/qt/count/");
    qDebug() << dir.mkpath("/home/fus/Git/MyTest/qt/count/main");
    qDebug() << dir.mkpath("/home/fus/Git/MyTest/qt/");
    qDebug() << dir.mkpath("/home/fus/Git/MyTest/qt/count/z/zz/zzz");
    qDebug() << dir.mkpath("q") << "===";
    //qDebug() << dir.rmpath("/home/fus/Git/MyTest/qt/count/main");

    return 0;

    QDir dir3("/home/fus/Git/MyTest/qt/count/main");
    qDebug() << dir3.removeRecursively();

    QDir dir4("/home/fus/Git/MyTest/qt/count/main/d/t/e");
    qDebug() << dir4.mkpath("") << "---";

    tptree ptree;
    ptree.put("a.b.c", "hello");

    QString value;
    qDebug() << get(ptree, "a.b.c", value) << ": " << value << endl;

    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL", "");
    database.setHostName("127.0.0.1");
    database.setPort(3306);
    database.setDatabaseName("mrgfusdb_neuro");
    database.setUserName("mrgfus");
    database.setPassword("mrgfus");
    if (!database.open()) {
        qDebug() << "connect failed: " << database.lastError().text();
    }
    else {
        qDebug() << "connect";
    }

    QSqlQuery query(database);
    if (!query.exec("update tbl_product set available = false where product_name = 'a'")) {
        qDebug() << "exec() failed";
    }
    else {
        qDebug() << "exec() success: " << query.numRowsAffected();
    }

    if (!query.exec("insert into tbl_product values('Bne Tumor', false)")) {
        qDebug() << "exec() failed: " << query.lastError().text() << query.lastError().type() << " " << query.lastError().nativeErrorCode();
    }
    else {
        qDebug() << "exec() success: " << query.numRowsAffected();
    }

    if (!query.exec("select * from tbl_series into outfile '/tmp/c.txt'")) {
        qDebug() << "exec() failed: " << query.lastError().text() << query.lastError().type() << " " << query.lastError().nativeErrorCode();
    }
    else {
        qDebug() << "exec() success: " << query.numRowsAffected() << "; " << query.size();
    }

    if (!query.exec("update tbl_product set available = true where product_name = 'Bne Tumor'")) {
        qDebug() << "exec() failed: " << query.lastError().text() << query.lastError().type() << " " << query.lastError().nativeErrorCode();
    }
    else {
        qDebug() << "exec() success: " << query.numRowsAffected() << "; " << query.size();
    }

    if (!query.exec("load data infile '/tmp/q.txt' replace into table tbl_product")) {
//        sleep(30);
        qDebug() << "exec() failed: " << query.lastError().text() << query.lastError().type() << " " << query.lastError().nativeErrorCode();
        qDebug() << "exec() failed: " << query.numRowsAffected() << "; " << query.size();
    }
    else {
        qDebug() << "exec() success: " << query.numRowsAffected() << "; " << query.size();
    }


    if (!query.exec("show errors")) {
        qDebug() << "exec() failed: " << query.lastError().text() << query.lastError().type() << " " << query.lastError().nativeErrorCode();
        qDebug() << "exec() failed: " << query.numRowsAffected() << "; " << query.size();
    }
    else {
        qDebug() << "exec() success: " << query.numRowsAffected() << "; " << query.size();
    }


    return 0;

    Counter a, b;
    QObject::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));

    a.setValue(12);

    QString s ="A9A0BC1234";

    qDebug() << QStringRef(&s, 0, 4).toLatin1() << endl;
    qDebug() << QStringRef(&s, 0, 4).toLatin1().toHex() << endl;
    qDebug() << QByteArray::fromHex(QStringRef(&s, 0, 4).toLatin1()) << endl;
    qDebug() << QByteArray::fromHex(QStringRef(&s, 0, 4).toLatin1()).toHex() << endl;

    /*
    QByteArray ba;
    ba.append(QStringRef(&s, 0, 1).toLatin1().toHex());
    ba.append(QStringRef(&s, 1, 1).toLatin1().toHex());
    ba.append(QStringRef(&s, 2, 2).toLatin1().toHex());

    qDebug() << ba[0] << endl;
    */

    return app.exec();
}
