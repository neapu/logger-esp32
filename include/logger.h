#pragma once

#include <string>
#include <source_location>
#include <format>
#include <sstream>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_DEBUG 4

#ifndef BUILD_LOG_LEVEL
#define BUILD_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#define FILE_NAME (strchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG(level, channel) \
    if (level > BUILD_LOG_LEVEL) ; \
    else Logger(level, channel, FILE_NAME, __LINE__, __func__)

#define LOG_ERROR(channel) LOG(LOG_LEVEL_ERROR, channel)
#define LOG_WARN(channel) LOG(LOG_LEVEL_WARN, channel)
#define LOG_INFO(channel) LOG(LOG_LEVEL_INFO, channel)
#define LOG_DEBUG(channel) LOG(LOG_LEVEL_DEBUG, channel)

class Logger final {
public:
    Logger(int level, const char* channel, const char* file, int line, const char* funcName);
    ~Logger();

    static void setLogLevel(int level) { s_logLevel = level; }
    static void init();

    template<typename T>
    Logger& operator<<(const T& value)
    {
        m_buffer << value;
        return *this;
    }

private:
    int m_level;
    const char* m_channel;
    const char* m_file;
    int m_line;
    const char* m_funcName;
    std::stringstream m_buffer;

    static int s_logLevel;
    static SemaphoreHandle_t s_mutex;
};
