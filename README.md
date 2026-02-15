# SyncLogging - 高性能多线程异步日志库

`SyncLogging` 是一个基于 C++11 编写的高性能、异步日志库。本项目参考了 muduo 的日志模块实现，采用**双缓冲（Double Buffering）机制**，旨在将磁盘 I/O 对业务线程的影响降到最低。

## 🌟 项目亮点

- **极致性能**：异步设计，支持每秒百万级别日志写入，前端几乎不阻塞。

- **双缓冲机制**：通过交换缓冲区指针，最大化减少锁竞争。

- **低开销格式化**：自定义 `LogStream` 类，避免 `std::stringstream` 的内存分配开销。

- **安全稳健**：采用 **RAII** 管理资源，支持日志文件滚动（Log Rolling）和自动刷新。

- **工程规范**：严格遵循 CMake 构建流程，代码模块化，包含完整的单元测试与基准测试。

## 🏗 核心架构
项目采用“前端-后端”分离模式：

- **前端 (Frontend)**：供业务线程调用，负责格式化日志消息到内存 Buffer。

- **后端 (Backend)**：独立线程负责将缓冲区数据定期、批量地写入磁盘。

## 🚀 快速开始

**编译**

``` bash
git clone https://github.com/yourname/SyncLogging.git
cd SyncLogging
mkdir build && cd build
cmake ..
make
```

**使用示例**

``` cpp
#include "Logger.h"

int main() {
    LOG_INFO << "Hello SyncLogging! The answer is " << 42;
    LOG_ERROR << "Something went wrong at " << 0.123;
}
```

## 工程目录说明
`src/`: 核心实现（LogStream, AsyncLogging, Logger）。

`base/`: 基础类封装（Thread, Mutex, Timestamp）。

`example/`: 快速上手示例。

`bench/`: 性能测试脚本与对比。
