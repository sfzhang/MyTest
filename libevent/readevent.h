/**
 * @file Read event
 *
 * @author sfzhang
 * @date 2016-4-19
 */

#ifndef READEVENT_H
#define READEVENT_H

#include "ievent.h"
#include <proto/socketbuffer.h>

namespace hifu { namespace mq {

/**
 * @class ReadEvent
 *
 * @brief Handle read event
 */
class ReadEvent: public IEvent {

public:

    /**
     * @brief Constructor
     */
    ReadEvent();

    /**
     * @brief Destructor
     */
    ~ReadEvent();

protected:

    /** 
     * @brief Get interesting events
     *
     * @return The interesting events
     */
    virtual short getEvents() const;

    /**
     * @brief Handle events
     *
     * @param[in] fd The socket fd
     * @param[in] events The flag of events
     */
    virtual void handleEvents(evutil_socket_t fd, short events);

protected:

    proto::SocketBuffer m_buffer;

};

} }

#endif
