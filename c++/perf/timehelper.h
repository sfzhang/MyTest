/**
 * @file Helper function or definition for time
 *
 * @author zhangshengfa
 * @date 2015-03-17
 */

#ifndef TIMEHELPER_H
#define TIMEHELPER_H

#include <sys/time.h>
#include <chrono>
#include <string>

#define USEC(t) ((t)->tv_sec * 1000000 + (t)->tv_usec)

#define TIME_INIT                                                       \
    std::chrono::time_point<std::chrono::high_resolution_clock> tm_t1_; \
    std::chrono::time_point<std::chrono::high_resolution_clock> tm_t2_; \

#define TIME_BEGIN tm_t1_ = std::chrono::high_resolution_clock::now()

#define TIME_END   tm_t2_ = std::chrono::high_resolution_clock::now()

#define TIME_SPEND(n)                                                   \
    do {                                                                \
        auto usec = std::chrono::duration_cast<                         \
                        std::chrono::microseconds>(tm_t2_ - tm_t1_);    \
        cout << "count: " << (n) << "\n"                                \
             << "total time: " << usec.count() << "(us)\n"              \
             << "per-time: " << usec.count() / (n) << "(us)" << endl;   \
    } while (0)

#endif /* !TIMEHELPER_H */
