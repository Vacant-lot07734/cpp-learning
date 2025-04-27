//
// Created by Vacant lot on 2025/4/7.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>
#include <functional>
#include <algorithm>
#include "../blockingqueue/blockingqueue.tpp"
#include "rejecthandle.h"


class MyThreadPool {
public:
    using Task = std::function<void()>;
    std::unique_ptr<BlockQueue<Task> > blockingQueue;
    RejectHandle *rejectHandle;

    // using RejectHandler = std::function<void(const Task &, MyThreadPool &)>;

    MyThreadPool(int coreSize, int maxSize, const std::chrono::milliseconds timeoutMs,
                 std::unique_ptr<BlockQueue<Task> > queue,
                 RejectHandle *rejectHandler)
        : corePoolSize(coreSize),
          maxPoolSize(maxSize),
          timeout(timeoutMs),
          blockingQueue(std::move(queue)),
          rejectHandle(rejectHandler) {
    }

    ~MyThreadPool() {
        shutdown();
    }

    void execute(Task task);

    void shutdown();

private:
    void startCoreThread(Task task);

    void startSupportThread(Task task);

    const int corePoolSize;
    const int maxPoolSize;
    const std::chrono::milliseconds timeout;

    std::vector<std::thread> coreThreads;
    std::vector<std::thread> supportThreads;

    std::mutex poolMutex;
    std::atomic<bool> isShutdown{false};
};


#endif //THREADPOOL_H
