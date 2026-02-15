// AsyncLogging.h
class AsyncLogging : noncopyable {
public:
    AsyncLogging(const string& basename, off_t rollSize, int flushInterval = 3);
    ~AsyncLogging();
    
    void append(const char* logline, int len);  // 前端调用
    void start();  // 启动后端线程
    
private:
    void threadFunc();  // 后端线程函数
    
    typedef FixedBuffer<kLargeBuffer> Buffer;  // 4MB
    typedef std::unique_ptr<Buffer> BufferPtr;
    typedef std::vector<BufferPtr> BufferVector;
    
    const int flushInterval_;  // 刷新间隔
    std::atomic<bool> running_;
    
    Thread thread_;
    CountDownLatch latch_;
    
    mutable MutexLock mutex_;
    Condition cond_;
    
    BufferPtr currentBuffer_;   // 当前缓冲区
    BufferPtr nextBuffer_;      // 预备缓冲区
    BufferVector buffers_;      // 待写入缓冲区队列
};
