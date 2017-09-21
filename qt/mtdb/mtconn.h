/**
 * @file Multi-thread connection
 *
 * @author sfzhang
 * @date 2017-9-21
 */

#ifndef MTCONN_H
#define MTCONN_H

#include <thread/thread.h>
#include <thread/ithreadworker.h>

class MtConn: public hifu::thread::IThreadWorker {

    Q_OBJECT

public slots:

    void connect();

    void quit();

};

#endif
