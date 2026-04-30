#include "logger.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main()
{
    // Initialize the logger mutex — call once before any logging
    Logger::init();

    LOG_INFO("DEMO")  << "Logger initialized. IDF version: " << IDF_VER;
    LOG_DEBUG("DEMO") << "Debug message, value = " << 42;
    LOG_WARN("DEMO")  << "Warn message, threshold = " << 3.14f;
    LOG_ERROR("DEMO") << "Error message, code = " << -1;

    // Stream multiple values in one call
    int a = 10, b = 20;
    LOG_INFO("MATH") << "a = " << a << ", b = " << b << ", sum = " << (a + b);

    // Runtime log level: suppress DEBUG and INFO
    Logger::setLogLevel(LOG_LEVEL_WARN);
    LOG_DEBUG("DEMO") << "This DEBUG message should NOT appear";
    LOG_INFO("DEMO")  << "This INFO message should NOT appear";
    LOG_WARN("DEMO")  << "This WARN message SHOULD appear";
    LOG_ERROR("DEMO") << "This ERROR message SHOULD appear";

    // Restore log level
    Logger::setLogLevel(LOG_LEVEL_DEBUG);
    LOG_INFO("DEMO") << "Log level restored to DEBUG";
}
