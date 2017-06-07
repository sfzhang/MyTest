/**
 * @file The log wrapper for log4cplus-1.1.2
 *
 * @author sfzhang 
 * @date 2014-08-24
 */

#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>
#include <string.h>

/** @brief Dump debug to stream */
#define _TRACE(stream, level, format, ...)                                  \
    fprintf(stream, "[" level "][%s:%s:%d] " format "\n", __FILE__,         \
            __func__, __LINE__, ##__VA_ARGS__)

/** @brief dump debug message to stdout */
#define DTRACE(format, ...)                                                 \
    _TRACE(stdout, "D", format, ##__VA_ARGS__)

/** @brief dump info message to stdout */
#define ITRACE(format, ...)                                                 \
    _TRACE(stdout, "I", format, ##__VA_ARGS__)

/** @brief dump warning message to stdout */
#define WTRACE(format, ...)                                                 \
    _TRACE(stdout, "W", format, ##__VA_ARGS__)

/** @brief dump error message to stderr */
#define ETRACE(format, ...)                                                 \
    _TRACE(stderr, "E", format, ##__VA_ARGS__)

/** @brief dump error message to stderr */
#define FTRACE(format, ...)                                                 \
    _TRACE(stderr, "F", format, ##__VA_ARGS__)

#endif
