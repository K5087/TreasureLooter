#pragma once
#define LOGI(fmt, ...)                         \
    do {                                       \
        logi(__FILE__, __LINE__, __FUNCTION__, \
             fmt __VA_OPT__(, ) __VA_ARGS__);  \
    } while (0)

#define LOGW(fmt, ...)                         \
    do {                                       \
        logw(__FILE__, __LINE__, __FUNCTION__, \
             fmt __VA_OPT__(, ) __VA_ARGS__);  \
    } while (0)

#define LOGE(fmt, ...)                         \
    do {                                       \
        loge(__FILE__, __LINE__, __FUNCTION__, \
             fmt __VA_OPT__(, ) __VA_ARGS__);  \
    } while (0)

#define LOGD(fmt, ...)                         \
    do {                                       \
        logd(__FILE__, __LINE__, __FUNCTION__, \
             fmt __VA_OPT__(, ) __VA_ARGS__);  \
    } while (0)

#define LOGC(fmt, ...)                         \
    do {                                       \
        logc(__FILE__, __LINE__, __FUNCTION__, \
             fmt __VA_OPT__(, ) __VA_ARGS__);  \
    } while (0)

#define LOGT(fmt, ...)                         \
    do {                                       \
        logt(__FILE__, __LINE__, __FUNCTION__, \
             fmt __VA_OPT__(, ) __VA_ARGS__);  \
    } while (0)
