#include <atomic>

class sharedCount {
public:
    sharedCount() = default;

    ~sharedCount() = default;

    sharedCount(const sharedCount &) = delete;

    sharedCount &operator=(const sharedCount &) = delete;

    void addCount() { count.fetch_add(1); }
    int getCount() const { return count.load(); }
    // 返回修改前的值
    int reduceCount() { return count.fetch_sub(1); }

private:
    std::atomic<int> count{1};
};

template<typename T>
class MysharedPtr {
public:
    explicit MysharedPtr(T *ptr) : ptr_(ptr) {
        counter_ = new sharedCount();
    }

    MysharedPtr(const MysharedPtr &other) : ptr_(other.ptr_) {
        counter_ = other.counter_;
        counter_->addCount();
    }

    MysharedPtr(MysharedPtr &&other) noexcept : ptr_(other.ptr_) {
        counter_ = other.counter_;
        other.counter_ = nullptr;
        other.ptr_ = nullptr;
    }

    MysharedPtr &operator=(const MysharedPtr &other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            counter_->addCount();
        }
        return *this;
    }

    MysharedPtr &operator=(MysharedPtr &&other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            other.counter_ = nullptr;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    ~MysharedPtr() {
        release();
    }

    T *get() {
        return ptr_;
    }

    T *operator->() {
        return ptr_;
    }

    T &operator*() {
        return *ptr_;
    }

private:
    void release() {
        if (counter_ && counter_->reduceCount() == 1) {
            delete ptr_;
            delete counter_;
        }
        ptr_ = nullptr;
        counter_ = nullptr;
    }

    T *ptr_{};
    sharedCount *counter_;
};
