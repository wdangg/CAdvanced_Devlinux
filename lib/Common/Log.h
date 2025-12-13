#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

#define LOG_INFO(fmt, ...) \
    fprintf(stderr, "[INFO] " fmt "\n", ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) \
    fprintf(stderr, "[WARNING] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)
#define LOG_PRINT(fmt, ...) \
    fprintf(stderr, "[LOG] " fmt "\n", ##__VA_ARGS__)

#endif /* _LOG_H_ */