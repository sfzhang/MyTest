/**
 * @file Write event implement
 *
 * @author sfzhang
 * @date 2016-4-19
 */

#include "writeevent.h"

#include <log/log.h>

#include <unistd.h>
#include <errno.h>

using namespace hifu::proto;

namespace hifu { namespace mq {

WriteEvent::WriteEvent():
    m_buffer(nullptr),
    m_pos(0),
    m_size(0)
{
}

WriteEvent::~WriteEvent()
{
}

void WriteEvent::setBuffer(const char *buffer, size_t size)
{
    m_buffer = buffer;
    m_size = size;
    m_pos = 0;

    int pending = event_pending(m_event, getEvents(), NULL);
    if (!pending) {
        if (!add()) {
            ELOG("add() failed");
            error();
        }
    }
}

short WriteEvent::getEvents() const
{
    return EV_WRITE;
}

void WriteEvent::handleEvents(evutil_socket_t fd, short events)
{
    if (events & EV_TIMEOUT) {
        timeout(fd);
    }
    else if (events & EV_WRITE) {
        while (1) {
            if (m_buffer && (m_pos < m_size)) {
                /* Write message */
                int ret = write(fd, (m_buffer + m_pos), (m_size - m_pos));
                if (ret < 0) {
                    if ((EAGAIN == errno) || (EWOULDBLOCK == errno)) {
                        WLOG("write() would block: errno[%d]", errno);
                        if (!add()) {
                            ELOG("add() write event failed");
                            error(fd);
                        }
                        break;
                    }
                    else {
                        ELOG("write() failed: errno[%d], fd[%d], m_buffer[%p], "
                             "m_pos[%u], m_size[%u]", errno, fd, m_buffer,
                             m_pos, m_size);
                        error(fd);
                        break;
                    }
                }
                else {
                    ILOG("write() success: ret[%d], fd[%d], m_buffer[%p], "
                         "m_pos[%u], m_size[%u]", ret, fd, m_buffer, m_pos,
                         m_size);

                    /* Update m_pos */
                    m_pos += ret;
                    if (m_pos == m_size) {
                        ILOG("All message was sent");
                        DDUMP(m_buffer, m_size);
                        success(fd);
                    } 
                    else {
                        WLOG("Part of message was sent: m_pos[%u], m_size[%u]",
                             m_pos, m_size);
                    }
                }
            }
        }
    }
    else {
        ELOG("Unknow events[%d]", events);
        error(fd);
    }
}

} }
