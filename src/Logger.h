// Logger.h: 前端用户接口
class Logger {
public:
    enum LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };
    
    Logger(const char* file, int line, LogLevel level);
    ~Logger();  // 析构时输出日志
    
    LogStream& stream() { return impl_.stream_; }
    
    static void setOutput(OutputFunc);  // 设置输出回调
    static void setLogLevel(LogLevel);
    
private:
    class Impl {
    public:
        Impl(LogLevel level, const char* file, int line);
        void formatTime();  // 格式化时间戳
        
        Timestamp time_;
        LogStream stream_;
        LogLevel level_;
        const char* basename_;
        int line_;
    };
    
    Impl impl_;
};

// 宏定义简化使用
#define LOG_INFO \
    if (Logger::logLevel() <= Logger::INFO) \
        Logger(__FILE__, __LINE__, Logger::INFO).stream()
