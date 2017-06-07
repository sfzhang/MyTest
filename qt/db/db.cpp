#include <QApplication>
#include <QHash>
#include <QString>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <string>
#include <QObject>

#include <log/log.h>
#include <dbsql/idbconnection.h>
#include <config/config.h>
#include <config/xmlparser.h>

using namespace std;
using namespace hifu;
using namespace hifu::log;
using namespace hifu::config;
using namespace hifu::dbsql;

bool insert_patient()
{
    QSqlDatabase database;
    if (!IDbConnection::instance()->database(database)) {
        qDebug() << "database() failed";
        return false;
    }

    QSqlQuery query(database);

    if (!query.prepare("insert into patient values('2', '3', 1, 1)")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed: " << query.lastError().text() <<
            "native error code: " << query.lastError().nativeErrorCode();
        return false;
    }

    qDebug() << "insert success";
    return true;
}

bool delete_patient()
{
    QSqlDatabase database;
    if (!IDbConnection::instance()->database(database)) {
        qDebug() << "database() failed";
        return false;
    }

    QSqlQuery query(database);

    if (!query.prepare("delete from patient where patient_id = '10'")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed" << query.lastError().text();
        return false;
    }

    qDebug() << "delete success:" << query.numRowsAffected();
    return true;
}

bool select_patient()
{
    QSqlDatabase database;
    if (!IDbConnection::instance()->database(database)) {
        qDebug() << "database() failed";
        return false;
    }

    QSqlQuery query(database);

    if (!query.prepare("select name from patient where patient_id = '10'")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        qDebug() << "have result";
    }
    else {
        if (query.lastError().type() != QSqlError::NoError) {
            qDebug() << "next() failed";
        }
        else {
            qDebug() << "no result";
        }
    }

    qDebug() << "select success:" << query.size();
    return true;
}

bool update_patient()
{
    QSqlDatabase database;
    if (!IDbConnection::instance()->database(database)) {
        qDebug() << "database() failed";
        return false;
    }

    QSqlQuery query(database);

    if (!query.prepare("update patient set name = '1' where patient_id = '2'")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed" << query.lastError().text() <<
            "error code: " << query.lastError().nativeErrorCode();
        return false;
    }

    qDebug() << "exec() update success" << query.lastError().text() <<
            "error code: " << query.lastError().nativeErrorCode();

    qDebug() << "update success:" << query.numRowsAffected();
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *label = new QLabel();

    string logfile = string(getenv("HIFU_ROOT")) + "/log/" + argv[0] + ".log";

    /* Initialize log */
    if (!initialize(argv[0])) {
        ETRACE("initialize() failed: progress_name[%s]", argv[0]);
        return -1;
    }

    string loglevel = "DEBUG";
    if (0 == argc) {
        loglevel = "ERROR";
    }
    else if (getenv(ENV_HIFU_LOG_LEVEL)) {
        loglevel = getenv(ENV_HIFU_LOG_LEVEL);
    }

    if (!setupLogger(string(argv[0]), loglevel, logfile)) {
        ELOG("setupLogger() failed");
        return -1;
    }

    tptree config_tree;
    if(!xmlparser::read(config_tree, "./db.xml")) {
        qDebug() << "read() failed";
        return -1;
    }

    if (!IDbConnection::instance()->load(config_tree)) {
        qDebug() << "load() failed";
        return -1;
    }

    if (!IDbConnection::instance()->transaction()) {
        qDebug() << "transaction() failed";
    }

    if (!insert_patient()) {
        qDebug() << "insert_patient() failed";
    }

    if (!delete_patient()) {
        qDebug() << "delete_patient() failed";
    }

    if (!select_patient()) {
        qDebug() << "select_patient() failed";
    }

    if (!update_patient()) {
        qDebug() << "update_patient() failed";
    }

    /*
    if (!IDbConnection::instance()->rollback()) {
        qDebug() << "rollback() failed";
        return -1;
    }
    */

    if (!IDbConnection::instance()->commit()) {
        qDebug() << "commit() failed";
    }

    IDbConnection::instance()->destroy();

    label->show();
    return app.exec();
}
