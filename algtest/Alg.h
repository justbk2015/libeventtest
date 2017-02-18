#pragma once
#include "project.h"

#ifdef __cplusplus
extern "C"
{
#endif

void test1();
int add(int a, int b);

#ifdef __cplusplus
};
#endif

extern zb::Log g_log;
#define logd(format, ...)  do {\
    g_log.debug(format, ## __VA_ARGS__);\
    g_log.flush();\
} while(0);

#define logi(format, ...)  do {\
    g_log.info(format, ## __VA_ARGS__);\
    g_log.flush();\
} while(0);
#define logw(format, ...)  do {\
    g_log.warn(format, ## __VA_ARGS__);\
    g_log.flush();\
} while(0);
#define loge(format, ...)  do {\
    g_log.error(format, ## __VA_ARGS__);\
    g_log.flush();\
} while(0);