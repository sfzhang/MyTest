/**
 * @file This file define some macro for dump message to stdout or stderr
 *
 * @author sfzhang
 * @date 2012-05-03
 */

#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

/**
 * @brief define errmsg
 */
#ifndef errmsg
#define errmsg strerror(errno)
#endif

/** @brief dump debug message */
#define DTRACE(fmt, ...) \
        fprintf(stdout, "[%s:%s:%d:D]"fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

/** @brief dump info message */
#define ITRACE(fmt, ...) \
        fprintf(stdout, "[%s:%s:%d:I]"fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

/** @brief dump warn message */
#define WTRACE(fmt, ...) \
        fprintf(stderr, "[%s:%s:%d:W]"fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

/** @brief dump err message*/
#define ETRACE(fmt, ...) \
        fprintf(stderr, "[%s:%s:%d:E]"fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#endif /* !TRACE_H */
