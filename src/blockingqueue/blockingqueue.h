//
// Created by Vacant lot on 2025/4/1.
//

#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#endif //BLOCKINGQUEUE_H
#include <mutex>
#include <condition_variable>
#include <deque>
#include <chrono>

template<class T>
class BlockQueue {
public:
    explicit BlockQueue(const int cap = -1) : m_maxCapacity(cap) {
    }

    ~BlockQueue() = default;

    BlockQueue(const BlockQueue &) = delete;

    BlockQueue &operator =(const BlockQueue &) = delete;

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    bool full() const {
        if (-1 == m_maxCapacity)
            return false;
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size() >= m_maxCapacity;
    }

    auto size() -> size_t {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    void put(T t);

    T take();

    bool poll(T &t);

    bool poll(T &t, std::chrono::milliseconds &time);

    bool offer(T t);

    bool offer(T t, std::chrono::milliseconds &time);

private:
    std::deque<T> m_queue;
    const int m_maxCapacity;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond_empty;
    std::condition_variable m_cond_full;
};
