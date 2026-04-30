# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.0] - 2026-04-30

### Added

- 初始独立发布（Initial standalone release）
- 流操作符 `<<` 日志 API（Stream operator `<<` logging API）
- 四个日志级别：`ERROR`、`WARN`、`INFO`、`DEBUG`（Four log levels）
- ANSI 颜色输出，ERROR=红、WARN=黄、INFO=绿、DEBUG=蓝（ANSI color output）
- 编译期裁剪宏 `BUILD_LOG_LEVEL`（Compile-time pruning via `BUILD_LOG_LEVEL`）
- 运行期动态级别切换 `Logger::setLogLevel`（Runtime level switching via `Logger::setLogLevel`）
- FreeRTOS 互斥锁保护多任务并发输出（FreeRTOS mutex for multi-task safe output）
- 自动附加时间戳、channel、CPU 核心、任务名、文件名、行号、函数名元数据头（Auto metadata header with timestamp, channel, CPU core, task name, file, line, function）
- `examples/hello_logger` 示例工程（Example project）
