//
// Created by Vacant lot on 2025/4/4.
//

#ifndef BQTEST2_H
#define BQTEST2_H
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <atomic>
#include "blockingqueue.tpp"

// 测试多个生产者和消费者同时操作队列
void test_multi_producer_consumer() {
    BlockQueue<int> q(10);
    const int producer_count = 4;
    const int consumer_count = 4;
    const int items_per_producer = 100;

    std::atomic<int> total_produced{0};
    std::atomic<int> total_consumed{0};

    std::vector<std::thread> producers, consumers;

    // 生产者线程
    for (int i = 0; i < producer_count; ++i) {
        producers.emplace_back([&]() {
            for (int j = 0; j < items_per_producer; ++j) {
                q.put(j);
                total_produced++;
            }
        });
    }

    // 消费者线程
    for (int i = 0; i < consumer_count; ++i) {
        consumers.emplace_back([&]() {
            for (int j = 0; j < (producer_count * items_per_producer) / consumer_count; ++j) {
                int val = q.take();
                total_consumed++;
                // 你也可以打印 val 看数据是否正确顺序（但可能乱序）
            }
        });
    }

    for (auto &p : producers) p.join();
    for (auto &c : consumers) c.join();

    assert(total_produced == producer_count * items_per_producer);
    assert(total_consumed == producer_count * items_per_producer);

    std::cout << "✅ test_multi_producer_consumer passed\n";
}

// 测试 shutdown 是否唤醒阻塞线程
void test_shutdown_wakes_threads() {
    BlockQueue<int> q(1);
    std::atomic<bool> take_threw{false};

    std::thread consumer([&]() {
        try {
            q.take(); // 一直阻塞
        } catch (const std::exception &e) {
            take_threw = true;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    q.shutdown();  // 应该唤醒 consumer 并抛异常

    consumer.join();
    assert(take_threw == true);
    std::cout << "✅ test_shutdown_wakes_threads passed\n";
}

// 测试多个 take 等待唤醒
void test_multiple_waiters() {
    BlockQueue<int> q(1);

    std::atomic<int> taken{0};
    std::vector<std::thread> threads;

    // 3 个线程都阻塞在 take 上
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back([&]() {
            try {
                int val = q.take();
                (void)val;
                taken++;
            } catch (...) {
                // 被 shutdown 唤醒也可以
            }
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 放 3 个数据，唤醒 3 个线程
    q.put(1);
    q.put(2);
    q.put(3);

    for (auto &t : threads) t.join();

    assert(taken == 3);
    std::cout << "✅ test_multiple_waiters passed\n";
}

int blockingqueueTest2() {
    test_multi_producer_consumer();
    test_shutdown_wakes_threads();
    test_multiple_waiters();
    std::cout << "✅ All multithreaded tests passed!\n";
    return 0;
}

#endif //BQTEST2_H
