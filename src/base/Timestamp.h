class Timestamp {
public:
    Timestamp() : microSecondsSinceEpoch_(0) {}
    explicit Timestamp(int64_t microSeconds) 
        : microSecondsSinceEpoch_(microSeconds) {}
    
    static Timestamp now();
    string toString() const;
    string toFormattedString(bool showMicroseconds = true) const;
    
private:
    int64_t microSecondsSinceEpoch_;  // 微秒精度
};
