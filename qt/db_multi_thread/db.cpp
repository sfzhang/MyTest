#include <QApplication>
#include <QHash>
#include <QString>
#include <QLabel>
#include <QThreadStorage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <string>
#include <QObject>

#include <log/log.h>
#include <dbsql/idbconnection.h>
#include <config/config.h>
#include <config/xmlparser.h>
#include <thread/ithreadworker.h>
#include <thread/thread.h>

#include "sqlworker.h"

using namespace std;
using namespace hifu;
using namespace hifu::config;
using namespace hifu::dbsql;
using namespace hifu::thread;

bool insert_patient()
{
    QSqlDatabase database;
    if (!IDbConnection::instance()->database(database)) {
        qDebug() << "database() failed";
        return false;
    }

    QSqlQuery query(database);

    if (!query.prepare("insert into patient values('3', '3', 1, 1)")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed";
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

    if (!query.prepare("delete from patient where patient_id = '1'")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed";
        return false;
    }

    qDebug() << "insert success";
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

    Thread *thread = new Thread("sql");
    SqlWorker *sql_worker = new SqlWorker();

    QObject::connect(thread, SIGNAL(finished()),
                     sql_worker, SLOT(deleteLater()));

    sql_worker->moveToThread(thread);
    thread->start();

    tptree config_tree;
    if(!xmlparser::read(config_tree, "./db.xml")) {
        qDebug() << "read() failed";
        return -1;
    }

    IDbConnection::instance()->enableMultiThread();

    if (!IDbConnection::instance()->load(config_tree)) {
        qDebug() << "load() failed";
        return -1;
    }

    QMetaObject::invokeMethod(sql_worker, "execute");

    if (!IDbConnection::instance()->transaction()) {
        qDebug() << "transaction() failed";
    }

    if (!insert_patient()) {
        qDebug() << "insert_patient() failed";
    }

    if (!delete_patient()) {
        qDebug() << "delete_patient() failed";
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

    QMetaObject::invokeMethod(sql_worker, "exit");

    label->show();
    return app.exec();
}
