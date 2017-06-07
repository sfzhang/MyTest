#include <log4cplus/loggingmacros.h>
//#include "loggingmacros.h"
#include <log4cplus/logger.h>
#include <log4cplus/streams.h>
#include <log4cplus/tstring.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/thread/threads.h>

#define LOG4CPLUS_LOGGER() \
    log4cplus::Logger::getInstance(log4cplus::thread::getCurrentThreadName2())

using namespace std;
using namespace log4cplus;

int main()
{
    size_t i = 1;

    LOG4CPLUS_MACRO_FMT_BODY(LOG4CPLUS_LOGGER(), DEBUG_LOG_LEVEL, "%s", i);

    /*
    helpers::snprintf_buf &sbuf = log4cplus::detail::get_macro_body_snprintf_buf ();
    sbuf.print("%s", i);
    */

    return 0;
}
