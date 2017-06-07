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

using namespace std;
using namespace hifu;
using namespace hifu::config;
using namespace hifu::dbsql;
using namespace hifu::thread;

class SqlWorker: public IThreadWorker{

    Q_OBJECT

public:

    SqlWorker(QObject *parent = NULL);

    ~SqlWorker();

public slots:

    void execute();
};
