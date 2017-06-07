/**
 * @file IEvent implement
 *
 * @author sfzhang
 * @date 2016-4-18
 */

#include "ievent.h"
#include <log/log.h>
#include <proto/socketbuffer.h>

using namespace hifu::proto;
namespace hifu { namespace mq {

IEvent::IEvent():
    m_event(nullptr)
{
}

IEvent::~IEvent()
{
    free();
}

void IEvent::timeout(evutil_socket_t fd)
{
    WLOG("Event[%x] timeout: fd[%d]", getEvents(), fd);
}

void IEvent::error(evutil_socket_t fd) 
{
    if (!remove()) {
        ELOG("remove() failed");
    }
    else {
        DLOG("remove() success");
    }

    if (evutil_closesocket(fd) != 0) {
        ELOG("evutil_closesocket() failed: fd[%d]", fd);
    }   
    else {
        DLOG("evutil_closesocket() success");
    }   
}

bool IEvent::initialize(struct event_base *base, evutil_socket_t fd)
{
    if (m_event) {
        ELOG("m_event[%p] has been initialize, call free() first", m_event);
        return false;
    }

    if ((!base) || (fd < 0)) {
        ELOG("Invalid argument(s): base[%p], fd[%d]", base, fd);
        return false;
    }

    short what = getEvents();
    m_event = event_new(base, fd, what, eventsHandler, this);
    if (!m_event) {
        ELOG("event_new() failed: base[%p], fd[%d], what[%x]", base, fd, what);
        return false;
    }
    DLOG("event_new() success: m_event[%p]", m_event);

    return true;
}

bool IEvent::add(int timeout)
{
    if (!m_event) {
        ELOG("m_event[%p] has NOT been initialize, call free() first", m_event);
        return false;
    }

    int ret = 0;
    if (timeout >= 0) {
        struct timeval tv;
        tv.tv_sec = timeout / 1000000;
        tv.tv_usec = timeout % 1000000;
        ret = event_add(m_event, &tv);
    }
    else {
        ret = event_add(m_event, nullptr);
    }

    if (ret != 0) {
        ELOG("event_add() failed: timeout[%d]", timeout);
        return false;
    }
    DLOG("event_add() success: timeout[%d]", timeout);

    return true;
}

bool IEvent::remove()
{
    if (!m_event) {
        ELOG("m_event[%p] has NOT been initialize, call free() first", m_event);
        return false;
    }

    int ret = event_del(m_event);
    if (ret != 0) {
        ELOG("event_del() failed");
        return false;
    }
    DLOG("event_del() success");

    return true;
}

void IEvent::free()
{
    if (m_event) {
        event_free(m_event);
        m_event = nullptr;
    }
}

void IEvent::eventsHandler(evutil_socket_t fd, short events, void *arg)
{
    IEvent *event = reinterpret_cast<IEvent*>(arg);
    if (!event) {
        ELOG("event is NULL");
        return;
    }

    event->handleEvents(fd, events);
}

} }
