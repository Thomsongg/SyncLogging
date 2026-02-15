class AppendFile : noncopyable {
public:
    explicit AppendFile(const string& filename);
    ~AppendFile();
    
    void append(const char* logline, size_t len);
    void flush();
    off_t writtenBytes() const { return writtenBytes_; }
    
private:
    size_t write(const char* logline, size_t len);
    
    FILE* fp_;
    char buffer_[64*1024];  // 64KB 用户缓冲区
    off_t writtenBytes_;
};

// 实现
void AppendFile::append(const char* logline, size_t len) {
    size_t written = 0;
    while (written != len) {
        size_t remain = len - written;
        size_t n = write(logline + written, remain);
        if (n != remain) {
            // 错误处理
        }
        written += n;
    }
    writtenBytes_ += written;
}
