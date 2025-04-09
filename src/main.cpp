//
// Created by Vacant lot on 2025/4/1.
//
#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

#include "../include/blockingqueue/blockingqueue.tpp"
#include "../include/threadpool/threadpool.h"
#include "../include/threadpool/rejecthandle.h"
using namespace std;
int main() {
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
