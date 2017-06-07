/**
 * @file Read event implement
 *
 * @author sfzhang
 * @date 2016-4-19
 */

#include "readevent.h"

#include <log/log.h>

using namespace hifu::proto;

namespace hifu { namespace mq {

ReadEvent::ReadEvent():
    m_buffer(10240)
{
}

ReadEvent::~ReadEvent()
{
}

short ReadEvent::getEvents() const
{
    return EV_READ | EV_PERSIST;
}

void ReadEvent::handleEvents(evutil_socket_t fd, short events)
{
    if (events & EV_TIMEOUT) {
        timeout(fd);
    }
    else if (events & EV_READ) {
        while (1) {
            /* Read header */
            if (0 == m_buffer.size()) {
                m_buffer.setPos(0);
                m_buffer.setSize(SocketBuffer::K_HEADER_SIZE);
            }
        
            int ret = m_buffer.recv(fd);
            if (ret < 0) {
                ELOG("recv() failed: fd[%d], ret[%d]", fd, ret);
                error(fd);
            }
            else if (0 == ret) {
                ILOG("recv() part of message");
            }
            else {
                DLOG("recv() all message");

                /* Header */
                if (SocketBuffer::K_HEADER_SIZE == m_buffer.size()) {
                    m_buffer.setPos(0);
                    SocketBuffer::SocketHeaderType length = 0;
                    m_buffer.readValue(length);
                    DLOG("length[%u]", length);
        
                    if (length != 0) {
                        m_buffer.setSize(SocketBuffer::K_HEADER_SIZE + length);
                        continue;
                    }
                }
    
                /* Message body */
                success(fd);
            }
            break;
        }
    }
    else {
        ELOG("Unknow events[%d]", events);
        error(fd);
    }
}

} }
