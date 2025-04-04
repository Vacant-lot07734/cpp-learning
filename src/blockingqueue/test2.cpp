//
// Created by Vacant lot on 2025/4/2.
//
#include <deque>
#include <mutex>
#include <condition_variable>
#include <chrono>

template<typename T>
class BlockingQueue {
public:
    // 构造时指定队列的最大容量
    explicit BlockingQueue(size_t capacity = 50) : capacity_(capacity) {
    }

    // 放入元素，如果队列已满则阻塞等待，直到有空间
    void put(const T &item) {
        // 阻塞时，自动释放锁权限，即调用unique_lock的成员函数unlock（），以便其他线程能有机会获得锁
        std::unique_lock<std::mutex> lock(mtx_);
        // 等待直到队列中元素个数小于容量
        cond_not_full_.wait(lock, [this]() { return queue_.size() < capacity_; });
        queue_.push_back(item);
        // 通知等待获取元素的线程
        cond_not_empty_.notify_one();
    }

    // 带超时的放入方法，如果在超时时间内无法放入，则返回 false
    bool offer(const T &item, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!cond_not_full_.wait_for(lock, timeout, [this]() { return queue_.size() < capacity_; })) {
            return false;
        }
        queue_.push(item);
        cond_not_empty_.notify_one();
        return true;
    }

    // 带超时的获取方法，如果在超时时间内没有元素则返回 false
    bool poll(T &item, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!cond_not_empty_.wait_for(lock, timeout, [this]() { return !queue_.empty(); })) {
            return false;
        }
        item = queue_.front();
        queue_.pop();
        cond_not_full_.notify_one();
        return true;
    }

    // 取出元素，如果队列为空则阻塞等待，直到有元素可取
    T take() {
        std::unique_lock<std::mutex> lock(mtx_);
        // 等待直到队列不为空
        cond_not_empty_.wait(lock, [this]() { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        // 通知等待放入元素的线程
        cond_not_full_.notify_one();
        return item;
    }

    // 返回队列中当前的元素个数
    size_t size() {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.size();
    }

private:
    std::deque<T> queue_;
    std::mutex mtx_;
    std::condition_variable cond_not_empty_;
    std::condition_variable cond_not_full_;
    size_t capacity_;
};
