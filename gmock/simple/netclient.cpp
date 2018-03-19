/**
 * @file Net client
 *
 * @author sfzhang
 * @date 2018-3-12
 */

#include "netclient.h"
#include <string>

bool NetClient::parse(INetStream &net_strm)
{
    std::string net_str = net_strm.getString();
    if (net_str.empty()) {
        return false;
    }
    else {
        return true;
    }
}
