#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/** @file */

//#define DEBUG

#ifdef DEBUG
/**
 * @brief Macro used to log error messages to stderr with printf's like format
 */
#define LOG_ERROR(...) do {\
fprintf(stderr, "[FILE: %s][LINE: %d] ", __FILE__, __LINE__);\
fprintf(stderr, __VA_ARGS__);\
fputc('\n', stderr);\
} while(0)
#else
/**
* @brief Macro used to log error messages to stderr with printf's like format
*/
#define LOG_ERROR(...)
#endif

/**
 * @brief Macro used to log messages to stdout with printf's like format
 */
#define LOG(...) do{\
fprintf(stdout, "[FILE: %s][LINE: %d] ", __FILE__, __LINE__);\
fprintf(stdout, __VA_ARGS__);\
fputc(stdout, __VA_ARGS__);\
} while(0)
#endif //LOG_H
