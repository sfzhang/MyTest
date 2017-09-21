/**
 * @file Multi-thread connection
 * @author sfzhang
 * @date 2017-9-21
 */

#include "mtconn.h"
#include <dbsql/idbconnection.h>
#include <log/log.h>

using namespace hifu;
using namespace hifu::log;
using namespace hifu::dbsql;

void MtConn::connect()
{
    if (!IDbConnection::instance()->load()) {
        ELOG("load() failed!");
    }
    else {
        DLOG("load() success!");
    }
}

void MtConn::quit()
{
    IDbConnection::instance()->destroy();
}
