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
#include <QMetaObject>

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

static bool insert_patient()
{
    QSqlQuery query;
    if (!IDbConnection::instance()->createQuery(query)) {
        qDebug() << "createQuery() failed";
        return false;
    }

    if (!query.prepare("insert into patient values('4', '4', 1, 1)")) {
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

bool update_patient()
{
    QSqlQuery query;
    if (!IDbConnection::instance()->createQuery(query)) {
        qDebug() << "createQuery() failed";
        return false;
    }

    if (!query.prepare("update patient set name = 'upd_name' where patient_id = '3'")) {
        qDebug() << "prepare() failed";
        return false;
    }

    if (!query.exec()) {
        qDebug() << "exec() failed";
        return false;
    }

    qDebug() << "update success";
    return true;
}

SqlWorker::SqlWorker(QObject *parent):
    IThreadWorker(parent)
{
}

SqlWorker::~SqlWorker()
{
}

void SqlWorker::execute()
{
    tptree config_tree;
    if(!xmlparser::read(config_tree, "./db.xml")) {
        qDebug() << "read() failed";
        return;
    }

    IDbConnection::instance()->enableMultiThread();

    if (!IDbConnection::instance()->load(config_tree)) {
        qDebug() << "load() failed";
        return;
    }

    if (!IDbConnection::instance()->transaction()) {
        qDebug() << "transaction() failed";
        return;
    }

    if (!insert_patient()) {
        qDebug() << "insert_patient() failed";
    }

    if (!update_patient()) {
        qDebug() << "delete_patient() failed";
    }

    if (!IDbConnection::instance()->commit()) {
        qDebug() << "commit() failed";
    }

    IDbConnection::instance()->destroy();
}
