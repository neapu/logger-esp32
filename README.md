# logger-esp32

一个为 ESP-IDF（ESP32 系列）设计的 C++ 日志库，支持流操作符（`<<`）和带自动元数据头的格式化输出。

## 特性

- 流式写法：`LOG_INFO("APP") << "value = " << val;`
- 自动输出格式：`[时间][channel][CPUx][TASK:任务名][文件:行号][函数名] 消息`
- ANSI 颜色：ERROR=红、WARN=黄、INFO=绿、DEBUG=蓝
- 四个日志级别：`ERROR` / `WARN` / `INFO` / `DEBUG`
- 编译期裁剪（`BUILD_LOG_LEVEL`）与运行期动态切换（`Logger::setLogLevel`）
- FreeRTOS 互斥保护，天然支持多任务并发输出
- 基于 C++20（`std::format`）

## 依赖

| 依赖 | 版本 |
|------|------|
| ESP-IDF | ≥ 6.0 |
| C++ 标准 | C++20 |

## 引用方式（git 依赖）

在你的工程 `main/idf_component.yml`（或组件的 `idf_component.yml`）中添加：

```yaml
dependencies:
  logger:
    git: "https://github.com/neapu/logger-esp32.git"
    version: ">=0.1.0"
```

然后执行：

```bash
idf.py reconfigure
```

## 快速使用

```cpp
#include "logger.h"

extern "C" void app_main()
{
    // 初始化互斥锁，在任何日志调用之前执行一次
    Logger::init();

    LOG_INFO("APP")  << "Hello, world!";
    LOG_DEBUG("APP") << "counter = " << 42;
    LOG_WARN("APP")  << "threshold exceeded: " << 3.14f;
    LOG_ERROR("APP") << "fatal error, code = " << -1;
}
```

输出示例：

```
[00:00:00.123][APP][CPU0][TASK:main][main.cpp:10][app_main] Hello, world!
```

## 日志级别

| 宏常量 | 值 | 颜色 |
|--------|----|------|
| `LOG_LEVEL_NONE`  | 0 | — |
| `LOG_LEVEL_ERROR` | 1 | 红 |
| `LOG_LEVEL_WARN`  | 2 | 黄 |
| `LOG_LEVEL_INFO`  | 3 | 绿 |
| `LOG_LEVEL_DEBUG` | 4 | 蓝 |

### 编译期裁剪

在工程的 `CMakeLists.txt` 或组件自身的 `CMakeLists.txt` 中定义，仅输出 `WARN` 及以上：

```cmake
target_compile_definitions(${COMPONENT_LIB} PRIVATE BUILD_LOG_LEVEL=2)
```

低于此级别的 `LOG_*` 宏在编译时会被 `if (level > BUILD_LOG_LEVEL) ;` 优化掉，不产生任何运行时开销。

### 运行期动态切换

```cpp
Logger::setLogLevel(LOG_LEVEL_WARN);  // 此后 INFO/DEBUG 不输出
Logger::setLogLevel(LOG_LEVEL_DEBUG); // 恢复全量输出
```

## 启用 C++20

ESP-IDF 6.0+ 工具链（GCC 15.x）默认使用 `gnu++26` 标准，`std::format` 等 C++20/23/26 特性开箱即用，无需额外配置。

## 许可证

[MIT](LICENSE) © 2026 Neapu

---

# logger-esp32 (English)

A C++ logging library for ESP-IDF (ESP32 series) that supports stream operator (`<<`) with auto metadata headers.

## Features

- Stream-style API: `LOG_INFO("APP") << "value = " << val;`
- Auto-formatted output: `[time][channel][CPUx][TASK:name][file:line][func] message`
- ANSI colors: ERROR=red, WARN=yellow, INFO=green, DEBUG=blue
- Four log levels: `ERROR` / `WARN` / `INFO` / `DEBUG`
- Compile-time pruning (`BUILD_LOG_LEVEL`) and runtime level switching (`Logger::setLogLevel`)
- FreeRTOS mutex-protected, safe for multi-task concurrent logging
- Requires C++20 (`std::format`)

## Requirements

| Dependency | Version |
|------------|---------|
| ESP-IDF    | ≥ 6.0   |
| C++ Standard | C++20 |

## Adding as a git dependency

In your project's `main/idf_component.yml`:

```yaml
dependencies:
  logger:
    git: "https://github.com/neapu/logger-esp32.git"
    version: ">=0.1.0"
```

Then run:

```bash
idf.py reconfigure
```

## Quick start

```cpp
#include "logger.h"

extern "C" void app_main()
{
    Logger::init();  // Initialize mutex — call once before any logging

    LOG_INFO("APP")  << "Hello, world!";
    LOG_DEBUG("APP") << "counter = " << 42;
    LOG_WARN("APP")  << "threshold exceeded: " << 3.14f;
    LOG_ERROR("APP") << "fatal error, code = " << -1;
}
```

Sample output:

```
[00:00:00.123][APP][CPU0][TASK:main][main.cpp:10][app_main] Hello, world!
```

## Log levels

| Macro | Value | Color |
|-------|-------|-------|
| `LOG_LEVEL_NONE`  | 0 | — |
| `LOG_LEVEL_ERROR` | 1 | Red |
| `LOG_LEVEL_WARN`  | 2 | Yellow |
| `LOG_LEVEL_INFO`  | 3 | Green |
| `LOG_LEVEL_DEBUG` | 4 | Blue |

### Compile-time pruning

```cmake
target_compile_definitions(${COMPONENT_LIB} PRIVATE BUILD_LOG_LEVEL=2)
```

Levels below the threshold are eliminated at compile time with zero runtime overhead.

### Runtime level switching

```cpp
Logger::setLogLevel(LOG_LEVEL_WARN);  // suppress INFO and DEBUG
Logger::setLogLevel(LOG_LEVEL_DEBUG); // restore all
```

## Enabling C++20

ESP-IDF 6.0+ with GCC 15.x defaults to `gnu++26`, so `std::format` and other C++20/23/26 features are available out of the box with no extra configuration required.

## License

[MIT](LICENSE) © 2026 Neapu
