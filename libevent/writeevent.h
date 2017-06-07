/**
 * @file Write event
 *
 * @author sfzhang
 * @date 2016-4-19
 */

#ifndef WRITEEVENT_H
#define WRITEEVENT_H

#include "ievent.h"
#include <proto/socketbuffer.h>
#include <pub/poolmanager.h>

namespace hifu { namespace mq {

/**
 * @class WriteEvent
 *
 * @brief Handle read event
 */
class WriteEvent: public IEvent {

public:

    /**
     * @brief Constructor
     */
    WriteEvent();

    /**
     * @brief Destructor
     */
    ~WriteEvent();

    /**
     * @brief Set buffer to send
     *
     * @param[in] buffer The buffer
     * @param[in] size The buffer size
     */
    void setBuffer(const char *buffer, size_t size);

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

    const char *m_buffer;
    size_t m_pos;
    size_t m_size;

};

} }

#endif
