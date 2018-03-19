/**
 * @file Net client
 *
 * @author sfzhang
 * @date 2018-3-12
 */

#ifndef NETCLIENT_H
#define NETCLIENT_H

#include "inetstream.h"
#include <string>

class NetClient {
public:

    virtual ~NetClient() {}
    virtual bool parse(INetStream &net_strm);

};

#endif
