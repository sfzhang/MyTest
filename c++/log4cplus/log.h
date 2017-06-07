#ifndef _LOG_H_
#define _LOG_H_

#include <log4cplus/loggingmacros.h>
//#include "loggingmacros.h"
#include <log4cplus/config.hxx>

#include <log4cplus/logger.h>
#include <log4cplus/streams.h>
#include <log4cplus/tstring.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/thread/threads.h>

#define LOG4CPLUS_LOGGER() \
    log4cplus::Logger::getInstance(log4cplus::thread::getCurrentThreadName2())

#if defined (LOG4CPLUS_HAVE_C99_VARIADIC_MACROS)
#define LOG4CPLUS_MACRO_FMT_BODY2(logger, logLevel, ...)                 \
    LOG4CPLUS_SUPPRESS_DOWHILE_WARNING()                                \
    do {                                                                \
        log4cplus::Logger const & _l                                    \
            = log4cplus::detail::macros_get_logger (logger);            \
        if (LOG4CPLUS_MACRO_LOGLEVEL_PRED (                             \
                _l.isEnabledFor (log4cplus::logLevel), logLevel)) {     \
            LOG4CPLUS_MACRO_INSTANTIATE_SNPRINTF_BUF (_snpbuf);         \
            log4cplus::tchar const * _logEvent                          \
                = _snpbuf.print (__VA_ARGS__);                          \
            log4cplus::detail::macro_forced_log (_l,                    \
                log4cplus::logLevel, _logEvent,                         \
                __FILE__, __LINE__, LOG4CPLUS_MACRO_FUNCTION ());       \
        }                                                               \
    } while(0)                                                          \
    LOG4CPLUS_RESTORE_DOWHILE_WARNING()
#endif

#endif
