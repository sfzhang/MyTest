#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "trace.h"

using namespace std;

bool convertToMicroseconds(chrono::microseconds &ms,
                           const string &date,
                           const string &time)
{
    /* Check date format */
    if (date.length() != 8) {
        ETRACE("Illegal date[%s]", date.c_str());
        return false;
    }

    /* Check time format */
    int length = time.length();
    if ((length < 2) || (3 == length) || (5 == length) ||
        (length > 14)) {
        ETRACE("Illegal time[%s]", time.c_str());
        return false;
    }

    size_t space_pos = time.find_first_of(' ');
    string time_ns = time; /* time without space */
    if (space_pos != string::npos) {
        for (int i = space_pos; i < length; i++) {
            if (time[i] != ' ') {
                ETRACE("Illegal time[%s]", time.c_str());
                return false;
            }
        }

        time_ns = time.substr(0, space_pos);
        length = time_ns.length();
        if ((length < 2) || (3 == length) || (5 == length) ||
            (length > 13)) { /* 13 for trimed space */
            ETRACE("Illegal time[%s]", time.c_str());
            return false;
        }
    }

    for (int i = 0; i < length; i++) {
        if (!isdigit(time_ns[i])) {
            if ((i != 6) || (time_ns[i] != '.')) {
                ETRACE("Illegal time[%s]", time.c_str());
                return false;
            }
        }
    }

    /* hour */
    stringstream sstrm;
    sstrm << time_ns.substr(0, 2);
    int hour = 0;
    sstrm >> hour;
    if ((!sstrm.eof()) || (hour < 0) || (hour > 23)) {
        ETRACE("Illegal time[%s]", time.c_str());
        return false;
    }
    DTRACE("hour[%d]", hour);
    sstrm.clear();
    sstrm.str("");

    int min = 0;
    int sec = 0;
    int usec = 0;
    if (length >= 4) {
        sstrm << time_ns.substr(2, 2);
        sstrm >> min;
        if ((!sstrm.eof()) || (min < 0) || (min > 59)) {
            ETRACE("Illegal time[%s]", time.c_str());
            return false;
        }
        DTRACE("min[%d]", min);
        sstrm.clear();
        sstrm.str("");

        if (length >= 6) {
            sstrm << time_ns.substr(4, 2);
            sstrm >> sec;
            if ((!sstrm.eof()) || (sec < 0) || (sec > 60)) {
                ETRACE("Illegal time[%s]", time.c_str());
                return false;
            }
            DTRACE("sec[%d]", sec);
            sstrm.clear();
            sstrm.str("");

            if (length > 6) {
                if (time_ns[6] != '.') {
                    ETRACE("Illegal time[%s]", time.c_str());
                    return false;
                }
                string value(6, '0');
                for (int i = 7; i < length; i++) {
                    value[i - 7] = time_ns[i];
                }

                sstrm << value;
                sstrm >> usec;
                if ((!sstrm.eof()) || (usec < 0) || (usec > 999999)) {
                    ETRACE("Illegal time[%s]", time.c_str());
                    return false;
                }
                DTRACE("usec[%d]", usec);
                sstrm.clear();
                sstrm.str("");
            }
        }
    }

    sstrm << date << " "
          << std::setw(2) << std::setfill('0') << hour << ":"
          << std::setw(2) << std::setfill('0') << min << ":"
          << std::setw(2) << std::setfill('0') << sec;
    DTRACE("date_time[%s]", sstrm.str().c_str());

    std::tm tm;
    if (!strptime(sstrm.str().c_str(), "%Y%m%d %H:%M:%S", &tm)) {
        ETRACE("strptime() failed: date[%s], time[%s]",
               date.c_str(), time.c_str());
        return false;
    }

    time_t t = std::mktime(&tm);
    if (-1 == t) {
        ETRACE("mktime() failed: date[%s], time[%s]", date.c_str(),
             time.c_str());
        return false;
    }
    DTRACE("mktime() success: t[%ld]", t);

    ms = chrono::seconds(t) + chrono::microseconds(usec);
    return true;
}

int main()
{
    chrono::microseconds ms;

    if (!convertToMicroseconds(ms, "19700102", "080010.100    ")) {
        ETRACE("convertToMicroseconds() failed");
        return -1;
    }

    DTRACE("convertToMicroseconds() success: ms[%ld]", ms.count());
    return 0;
}
