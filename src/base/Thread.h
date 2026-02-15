class Thread : noncopyable {
public:
    typedef std::function<void()> ThreadFunc;
    
    explicit Thread(ThreadFunc, const string& name = string());
    ~Thread();
    
    void start();
    int join();
    bool started() const { return started_; }
    
private:
    static void* startThread(void* obj);
    void runInThread();
    
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    ThreadFunc func_;
    string name_;
    CountDownLatch latch_;
};
