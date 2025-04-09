#include <iostream>
#include <thread>
#include <cassert>
#include <vector>
#include <chrono>
#include "blockingqueue.tpp"

void test_basic_put_take() {
    BlockQueue<int> q(2);
    q.put(1);
    q.put(2);
    assert(q.Size() == 2);
    int a = q.take();
    int b = q.take();
    assert(a == 1);
    assert(b == 2);
    std::cout << "✅ test_basic_put_take passed\n";
}

void test_offer_poll() {
    BlockQueue<int> q(1);
    assert(q.offer(42) == true);
    assert(q.offer(99) == false); // already full

    int value;
    assert(q.poll(value) == true && value == 42);
    assert(q.poll(value) == false); // empty
    std::cout << "✅ test_offer_poll passed\n";
}

void test_timeout_offer_poll() {
    BlockQueue<int> q(1);
    assert(q.offer(1) == true);

    // Should time out
    auto start = std::chrono::steady_clock::now();
    bool success = q.offer(2, std::chrono::milliseconds(100));
    auto end = std::chrono::steady_clock::now();
    assert(success == false);
    assert(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= 100);

    int val;
    assert(q.poll(val, std::chrono::milliseconds(100)) == true);
    assert(val == 1);
    std::cout << "✅ test_timeout_offer_poll passed\n";
}

void test_blocking_behavior() {
    BlockQueue<int> q(1);

    std::thread producer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        q.put(123);
    });

    auto start = std::chrono::steady_clock::now();
    int value = q.take(); // will block until producer puts value
    auto end = std::chrono::steady_clock::now();

    assert(value == 123);
    assert(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= 100);
    producer.join();
    std::cout << "✅ test_blocking_behavior passed\n";
}

void test_shutdown_behavior() {
    BlockQueue<int> q(1);
    q.put(1);

    q.shutdown();

    try {
        q.add(2);
        assert(false); // should not reach here
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) == "BlockQueue is shutdown");
    }

    try {
        q.remove();
    } catch (...) {
        // allowed
    }

    int val = 0;
    assert(q.offer(3) == false);
    assert(q.poll(val) == false);
    assert(q.poll(val, std::chrono::milliseconds(100)) == false);
    assert(q.offer(4, std::chrono::milliseconds(100)) == false);

    try {
        q.take();
        assert(false);
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) == "Queue is shutdown");
    }

    std::cout << "✅ test_shutdown_behavior passed\n";
}

int blockingqueueTest() {
    test_basic_put_take();
    test_offer_poll();
    test_timeout_offer_poll();
    test_blocking_behavior();
    test_shutdown_behavior();
    std::cout << "✅ All tests passed!\n";
    return 0;
}