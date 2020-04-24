#ifndef LOG_H
#define LOG_H

#include <stdio.h>
//
//#define DEBUG

#ifdef DEBUG
#define LOG_ERROR(...) do {\
fprintf(stderr, "[FILE: %s][LINE: %d] ", __FILE__, __LINE__);\
fprintf(stderr, __VA_ARGS__);\
fputc('\n', stderr);\
} while(0)
#else
#define LOG_ERROR(...)
#endif


#define LOG(...) do{\
fprintf(stdout, "[FILE: %s][LINE: %d] ", __FILE__, __LINE__);\
fprintf(stdout, __VA_ARGS__);\
fputc(stdout, __VA_ARGS__);\
} while(0)
#endif //LOG_H
