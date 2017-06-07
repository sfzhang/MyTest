/**
 * @file Event interface
 *
 * @author sfzhang
 * @date 2016-4-19
 */

#ifndef IEVENT_H
#define IEVENT_H

#include "mqdef.h"
#include <event2/event.h>

struct event;
struct event_base;

namespace hifu { namespace mq {

/**
 * @class IEvent
 *
 * @brief Event wrapper for libevent
 */
class IEvent {

public:

    /**
     * @brief Constructor
     */
    IEvent();

    /**
     * @brief Destructor
     */
    ~IEvent();

    /**
     * @brief Initialize the event
     *
     * @param[in] base The event base
     * @param[in] fd The socket fd
     *
     * @return true if succeed, otherwise false
     */
    bool initialize(struct event_base *base, evutil_socket_t fd);

    /**
     * @brief Add the event to base
     *
     * @param[in] timeout The timeout in ms, -1 cause block indefinitely
     *
     * @return true if succeed, otherwise false
     */
    bool add(int timeout = -1);

    /**
     * @brief Remove the event from base
     *
     * @return true if succeed, otherwise false
     */
    bool remove();

    /**
     * @brief Free the event
     */
    void free();

    /**
     * @brief Callback function
     *
     * @param[in] fd The socket fd
     * @param[in] events The flag of events
     * @param[in] arg The argument
     */
    static void eventsHandler(evutil_socket_t fd, short events, void *arg);

protected:

    /**
     * @brief Handle timeout event
     *
     * @param[in] fd The socket fd
     */
    virtual void timeout(evutil_socket_t fd);

    /**
     * @brief Handle error event
     *
     * @param[in] fd The socket fd
     */
    virtual void error(evutil_socket_t fd);

    /**
     * @brief Handle success
     *
     * @param[in] fd The socket fd
     */
    virtual void success(evutil_socket_t fd) = 0;

    /**
     * @brief Get interesting events
     *
     * @return The interesting events
     */
    virtual short getEvents() const = 0;

    /**
     * @brief Handle events
     *
     * @param[in] fd The socket fd
     * @param[in] events The flag of events
     */
    virtual void handleEvents(evutil_socket_t fd, short events) = 0;

protected:

    struct event *m_event;

};

} }

#endif
