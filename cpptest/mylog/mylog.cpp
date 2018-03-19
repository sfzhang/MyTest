#include <iostream>
#include <iomanip>
#include <log4cplus/tstring.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/thread/threads.h>
#include <log4cplus/configurator.h>

using namespace std;

void setThreadName(const log4cplus::tstring &name)
{
    try {
        log4cplus::thread::setCurrentThreadName2(name);
    }
    catch (...) {
        log4cplus::tcerr << LOG4CPLUS_TEXT("setCurrentThreadName2() failed!")
                         << std::endl;
    }
}

log4cplus::tstring formatBuffer(const void *buffer, unsigned int size)
{
    const unsigned char *b = reinterpret_cast<const unsigned char *>(buffer);

    /* Format using ostringstream */
    LOG4CPLUS_MACRO_INSTANTIATE_OSTRINGSTREAM(oss);
    oss << std::hex; /* Integer type */

    /* Begin width '\n' */
    oss << LOG4CPLUS_TEXT('\n');

    /* Format */
    unsigned int i = 0;
    unsigned int j = 0;

    while (i < size) {
        j = i;

        /* Fill with 0 */
        oss << std::setfill(LOG4CPLUS_TEXT('0'));

        /* Length */
        oss << std::setw(8) << i << LOG4CPLUS_TEXT(" | ");

        /* Hex data */
        while ((i < size) && ((i - j) < 16)) {
            oss << std::setw(2) << static_cast<unsigned int>(b[i]);

            if (1 == (i % 2)) {
                oss << LOG4CPLUS_TEXT(' ');
            }

            i++;
        }

        /* Remainder */
        if ((i - j) < 16) {
            oss << std::setfill(LOG4CPLUS_TEXT(' ')); /* Fill with space */
            oss << std::setw((16 - (i - j)) * 2 + (16 - (i - j) + 1) / 2)
               << LOG4CPLUS_TEXT(' ');
        }

        /* Separator */
        oss << LOG4CPLUS_TEXT("| ");

        /* Value */
        i = j;
        while ((i < size) && ((i - j) < 16)) {
            if (static_cast<unsigned int>(b[i]) < 33) {
                oss << LOG4CPLUS_TEXT('.');
            }
            else if (static_cast<unsigned int>(b[i]) > 126) {
                oss << LOG4CPLUS_TEXT('*');
            }
            else {
                oss << static_cast<char>(b[i]);
            }
            i++;
        }

        if (i < size) {
            oss << LOG4CPLUS_TEXT('\n');
        }
    }

    return oss.str();
}
