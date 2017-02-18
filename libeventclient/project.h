#pragma once
#ifndef USE_LOG_DLL
#define USE_LOG_DLL
#endif
#include "../commonlog/include/Log.h"
#pragma comment(lib, "../commonlog/lib/x64/Debug/common_log.lib")
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