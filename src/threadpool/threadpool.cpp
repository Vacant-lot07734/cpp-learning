//
// Created by Vacant lot on 2025/4/7.
//
#include "threadpool/threadpool.h"
#include <iostream>

void MyThreadPool::execute(Task task) {
    std::unique_lock<std::mutex> lock(poolMutex);
    if (static_cast<int>(coreThreads.size()) < corePoolSize) {
        startCoreThread(std::move(task));
        return;
    }
    if (blockingQueue->offer(task)) {
        return;
    }
    if (static_cast<int>(coreThreads.size() + supportThreads.size()) < maxPoolSize) {
        startSupportThread(std::move(task));
        return;
    }
    if (!blockingQueue->offer(task)) {
        // 拒绝操作
        rejectHandle->reject(task,this);
    }
}

void MyThreadPool::shutdown() {
    // 整个操作是原子(原子的读-修改-写操作)
    // value不受其他线程之间的即时影响它的值是读取(返回),现在是修改这个函数。
    if (isShutdown.exchange(true)) return;
    blockingQueue->shutdown();
    for (auto &t: coreThreads) {
        if (t.joinable()) t.join();
    }
    for (auto &t: supportThreads) {
        if (t.joinable()) t.join();
    }
    std::cout<<"ThreadPool shutdown"<<std::endl;
}

void MyThreadPool::startCoreThread(Task task) {
    coreThreads.emplace_back([this, task = std::move(task)]() mutable {
        task();
        while (!isShutdown.load()) {
            if (Task next = blockingQueue->take()) {
                next();
            }
        }
    });
}

void MyThreadPool::startSupportThread(Task task) {
    supportThreads.emplace_back([this, task = std::move(task)]() mutable {
        task();
        while (!isShutdown.load()) {
            Task next;
            if (!blockingQueue->poll(next, timeout)) {
                break; // timeout，线程退出
            }
            next();
        }

        std::cout << std::this_thread::get_id() << " support thread ended.\n";

        std::unique_lock<std::mutex> lock(poolMutex);
        auto id = std::this_thread::get_id();
        auto it = std::find_if(supportThreads.begin(), supportThreads.end(),
                               [id](std::thread &t) { return t.get_id() == id; });
        if (it != supportThreads.end()) {
            it->detach(); // 防止悬挂线程
            supportThreads.erase(it);
        }
    });
}
