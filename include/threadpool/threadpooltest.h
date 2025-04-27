//
// Created by Vacant lot on 2025/4/15.
//
#pragma once
#include <functional>
#include <iostream>
#include <thread>
#include <algorithm>
#include "blockingqueue/blockingqueue.tpp"
#include "threadpool.h"
#include "rejecthandle.h"
using namespace std;
void inline threadpooltest() {
    auto bq = make_unique<BlockQueue<std::function<void()> > >(6);
    ThrowRejectHandle *rh = new ThrowRejectHandle();

    auto mpool = make_unique<MyThreadPool>(4, 10, std::chrono::milliseconds(10),
                                           std::move(bq), rh);

    for (int i = 0; i < 10; ++i) {
        try {
            mpool->execute(
                std::bind([i]() {
                    std::cout << "Task " << i << " on thread " << std::this_thread::get_id() << std::endl;
                }));
        } catch (const std::exception &e) {
            cout << e.what() << endl;
        }
    }
}