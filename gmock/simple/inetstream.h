/**
 * @file net stream interface
 *
 * @author sfzhang
 * @date 2018-3-12
 */

#ifndef INETSTREAM_H
#define INETSTREAM_H

#include <string>

class INetStream {
public:

    virtual ~INetStream() {}
    virtual std::string getString() = 0;

};

#endif
