class LogFile : noncopyable {
public:
    LogFile(const string& basename, off_t rollSize, 
            int flushInterval = 3, int checkEveryN = 1024);
    
    void append(const char* logline, int len);
    void flush();
    bool rollFile();  // 滚动文件
    
private:
    void append_unlocked(const char* logline, int len);
    static string getLogFileName(const string& basename, time_t* now);
    
    const string basename_;
    const off_t rollSize_;       // 文件大小阈值
    const int flushInterval_;    // 刷新时间间隔
    const int checkEveryN_;      // 检查频率
    
    int count_;
    time_t startOfPeriod_;       // 按天滚动
    time_t lastRoll_;
    time_t lastFlush_;
    
    std::unique_ptr<FileUtil::AppendFile> file_;
    const static int kRollPerSeconds_ = 60*60*24;  // 一天
};
