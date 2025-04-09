//
// Created by Vacant lot on 2025/4/7.
//

#ifndef REJECTHANDLE_H
#define REJECTHANDLE_H
#include <functional>
class MyThreadPool;

class RejectHandle {
public:
    virtual ~RejectHandle() = default;

    virtual void reject(std::function<void()> &rejectCommand, MyThreadPool *mPool) = 0;
};

class ThrowRejectHandle : public RejectHandle {
public:
    ~ThrowRejectHandle() override = default;

    void reject(std::function<void()> &rejectCommand, MyThreadPool *mPool) override;
};

class DiscardRejectHandle : public RejectHandle {
public:
    ~DiscardRejectHandle() override = default;

    void reject(std::function<void()> &rejectCommand, MyThreadPool *mPool) override;
};

#endif //REJECTHANDLE_H
