//
// Created by Vacant lot on 2025/4/1.
//

#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
#include <mutex>
#include <condition_variable>
#include <deque>
#include <chrono>
// 可以进一步优化的点：
// 阻塞等待时间不局限与chrono::milliseconds,使用模板支持更多
template<class T>
class BlockQueue {
public:
    explicit BlockQueue(const int cap = 50) : m_maxCapacity(cap) {
    }

    ~BlockQueue() {
        shutdown();
    }

    BlockQueue(const BlockQueue &) = delete;

    BlockQueue &operator =(const BlockQueue &) = delete;

    void shutdown() { {
            std::lock_guard<std::mutex> lock(m_mutex);
            is_shutdown.store(true);
            m_queue.clear();
        }
        m_not_empty.notify_all();
        m_not_full.notify_all();
    }

    auto Size() -> size_t {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    // 失败抛出异常
    template<class U>
    void add(U &&t);

    // 一直阻塞
    template<class U>
    void put(U &&t);

    // 失败返回false
    template<class U>
    bool offer(U &&t);

    // 超时退出
    template<class U>
    bool offer(U &&t, const std::chrono::milliseconds &time);

    // 失败抛出异常
    T remove();

    // 一直阻塞
    T take();

    // 失败返回false
    bool poll(T &t);

    // 超时退出
    bool poll(T &t, const std::chrono::milliseconds &time);

private:
    std::deque<T> m_queue;
    const int m_maxCapacity;
    mutable std::mutex m_mutex;
    std::condition_variable m_not_empty;
    std::condition_variable m_not_full;
    // bool is_shutdown{false}; 没必要使用互斥锁，开销大
    std::atomic<bool> is_shutdown{false};

    // 下面函数不加锁，防止死锁
    bool full() const {
        return m_queue.size() >= m_maxCapacity;
    }

    bool empty() const {
        return m_queue.empty();
    }
};

// 第一个是类模版
// 第二个是函数模版
// 这样写稍显复杂，可以直接在类定义中实现，不必分开
template<class T>
template<class U>
void BlockQueue<T>::add(U &&t) {
    if (is_shutdown.load()) throw std::runtime_error("BlockQueue is shutdown");
    std::lock_guard<std::mutex> guard(m_mutex);
    if (this->full()) {
        // 出作用域，锁会正常释放
        throw std::runtime_error("Queue is full");
    }
    m_queue.push_back(std::forward<U>(t));
    m_not_empty.notify_one();
}

template<class T>
template<class U>
void BlockQueue<T>::put(U &&t) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_not_full.wait(lock, [&] { return !this->full() || is_shutdown.load(); });
    if (is_shutdown.load()) return;
    m_queue.push_back(std::forward<U>(t));
    m_not_empty.notify_one();
}

template<class T>
template<class U>
bool BlockQueue<T>::offer(U &&t) {
    if (is_shutdown.load()) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    if (this->full()) {
        return false;
    }
    m_queue.push_back(std::forward<U>(t));
    m_not_empty.notify_one();
    return true;
}

template<class T>
template<class U>
bool BlockQueue<T>::offer(U &&t, const std::chrono::milliseconds &time) {
    std::unique_lock<std::mutex> lock(m_mutex);
    bool result = m_not_full.wait_for(lock, time,
                                      [&] { return !this->full() || is_shutdown.load(); });
    if (is_shutdown.load()) return false;
    if (!result) {
        return false;
    }
    m_queue.push_back(std::forward<U>(t));
    m_not_empty.notify_one();
    return true;
}

template<class T>
T BlockQueue<T>::remove() {
    if (is_shutdown.load()) throw std::runtime_error("Queue is shutdown");
    std::lock_guard<std::mutex> lock(m_mutex);
    if (this->empty()) {
        throw std::runtime_error("Queue is empty");
    }
    auto res = m_queue.front();
    m_queue.pop_front();
    m_not_full.notify_one();
    return res;
}

template<class T>
T BlockQueue<T>::take() {
    std::unique_lock<std::mutex> lock(m_mutex);
    // take必须判断队列为空
    m_not_empty.wait(lock, [&]() { return !this->empty() || is_shutdown.load(); });
    if (is_shutdown.load()) throw std::runtime_error("Queue is shutdown");
    auto res = m_queue.front();
    m_queue.pop_front();
    m_not_full.notify_one();
    return res;
}

template<class T>
bool BlockQueue<T>::poll(T &t) {
    if (is_shutdown.load()) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    if (this->empty()) {
        return false;
    }
    t = m_queue.front();
    m_queue.pop_front();
    m_not_full.notify_one();
    return true;
}

template<class T>
bool BlockQueue<T>::poll(T &t, const std::chrono::milliseconds &time) {
    std::unique_lock<std::mutex> lock(m_mutex);
    bool result = m_not_empty.wait_for(lock, time,
                                       [&] { return !m_queue.empty() || is_shutdown.load(); });
    if (is_shutdown.load()) return false;
    if (!result) {
        return false;
    }
    t = m_queue.front();
    m_queue.pop_front();
    m_not_full.notify_one();
    return true;
}

#endif //BLOCKINGQUEUE_H
