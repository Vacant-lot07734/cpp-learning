#include <atomic>

template<typename T>
class mysharedptr {
public:
    explicit mysharedptr(T *ptr) : ptr_(ptr) {
        counter_ = new int(1);
        cnt_.fetch_add(1, std::memory_order_relaxed);
    };

    ~mysharedptr();

    T *get() {
        return ptr_;
    }

private:
    T *ptr_;
    int *counter_;
    std::atomic<int> cnt_;
};
