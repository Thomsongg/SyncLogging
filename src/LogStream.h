/*
 * LogStream 的同步版，后续转化为异步模式
 * 使用 char* 代替 std::string 防止频繁申请内存的开销
 * 1. 申请一块固定大小的内存（比如 4KB）。
 * 2. 用一个指针 cur_ 记录当前写到了哪里。
 * 3. 提供一个 append 方法往里塞数据。
 */
template<int SIZE>
class FixedBuffer {
public:
    FixedBuffer() : cur_(data_) {}

    void append(const char* buf, size_t len) {
        if (avail() > static_cast<int>(len)) {
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }

    int avail() const { return static_cast<int>(end() - cur_); }
    const char* data() const { return data_; }
    int length() const { return static_cast<int>(cur_ - data_); }

private:
    const char* end() const { return data_ + SIZE; }
    char data_[SIZE];
    char* cur_;
};
