#include "logger.h"
#include <iostream>
#include <format>
#include <print>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static std::string getTimeString()
{
    int64_t us = esp_timer_get_time();
    int64_t ms = us / 1000;
    int64_t hh = ms / 3600000;
    int64_t mm = (ms % 3600000) / 60000;
    int64_t ss = (ms % 60000) / 1000;
    int64_t zzz = ms % 1000;
    return std::format("{:02d}:{:02d}:{:02d}.{:03d}", hh, mm, ss, zzz);
}

int Logger::s_logLevel = LOG_LEVEL_DEBUG;
SemaphoreHandle_t Logger::s_mutex = nullptr;

void Logger::init()
{
    if (s_mutex == nullptr) {
        s_mutex = xSemaphoreCreateMutex();
    }
}

Logger::Logger(int level, const char* channel, const char* file, int line, const char* funcName)
    : m_level(level), m_channel(channel), m_file(file), m_line(line), m_funcName(funcName)
{
}

Logger::~Logger()
{
    if (m_level == LOG_LEVEL_NONE || m_level > s_logLevel) {
        return;
    }
    
    const char* taskName = pcTaskGetName(xTaskGetCurrentTaskHandle());
    int coreId = xPortGetCoreID();

    const char* color = "";
    const char* reset = "\033[0m";
    switch (m_level) {
        case LOG_LEVEL_ERROR: color = "\033[31m"; break; // 红色
        case LOG_LEVEL_WARN:  color = "\033[33m"; break; // 黄色
        case LOG_LEVEL_INFO:  color = "\033[32m"; break; // 绿色
        case LOG_LEVEL_DEBUG: color = "\033[34m"; break; // 蓝色
        default: reset = ""; break;
    }

    std::string header = std::format("[{}][{}][CPU{}][TASK:{}][{}:{}][{}] ", 
        getTimeString(),
        m_channel,
        coreId,
        taskName ? taskName : "?",
        m_file, 
        m_line, 
        m_funcName
    );
    if (s_mutex) xSemaphoreTake(s_mutex, portMAX_DELAY);
    std::cout << color << header << m_buffer.str() << reset << std::endl;
    if (s_mutex) xSemaphoreGive(s_mutex);
}
