//
// Created by Vacant lot on 2025/4/7.
//
#include "threadpool/rejecthandle.h"
#include "threadpool/threadpool.h"
#include "blockingqueue/blockingqueue.tpp"

void ThrowRejectHandle::reject(std::function<void()> &rejectCommand, MyThreadPool *mPool) {
    {
        throw std::runtime_error("blocking queue is full");
    }
}

void DiscardRejectHandle::reject(std::function<void()> &rejectCommand, MyThreadPool *mPool) {
    {
        mPool->blockingQueue->take();
        mPool->execute(rejectCommand);
    }
}
