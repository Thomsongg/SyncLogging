/*
 * LogStream: 前端高性能缓冲
 * 核心: 固定大小栈上缓冲区 + 手工整数转字符串
 * 使用 char* 代替 std::string 防止频繁申请内存的开销
 * 1. 申请一块固定大小的内存（比如 4KB）。
 * 2. 用一个指针 cur_ 记录当前写到了哪里。
 * 3. 提供一个 append 方法往里塞数据。
 */

// LogStream.h 关键设计
class LogStream : noncopyable {
public:
    typedef FixedBuffer<kSmallBuffer> Buffer;  // 4KB 缓冲区
    
    LogStream& operator<<(int);
    LogStream& operator<<(const char*);
    // ... 其他类型的重载
    
    const Buffer& buffer() const { return buffer_; }
    void resetBuffer() { buffer_.reset(); }
    
private:
    Buffer buffer_;
    
    // 关键:手工实现整数转字符串(比 snprintf 快 10 倍)
    template<typename T>
    void formatInteger(T);
};

// FixedBuffer 实现
template<int SIZE>
class FixedBuffer : noncopyable {
public:
    void append(const char* data, size_t len) {
        if (avail() > len) {
            memcpy(cur_, data, len);
            cur_ += len;
        }
    }
    
    const char* data() const { return data_; }
    int length() const { return static_cast<int>(cur_ - data_); }
    int avail() const { return static_cast<int>(end() - cur_); }
    
private:
    char data_[SIZE];
    char* cur_;
};
