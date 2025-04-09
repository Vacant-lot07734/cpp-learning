//
// Created by Vacant lot on 2025/4/7.
//

#ifndef THREAD_H
#define THREAD_H
#include <future>
#include <thread>
#include <iostream>

class ThreadTest {
public:
    void ThreadTest1() {
        using namespace std;
        std::cout << "Thread will sleep for 3 seconds..." << std::endl;
        auto x = thread([&]() {
            for (int i = 0; i < 3; i++) {
                cout << "T_X Hello World!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        });
        auto y = thread([&]() {
            for (int i = 0; i < 3; i++) {
                cout << "T_Y Hello World!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        });
        // 让当前线程暂停3秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Main Thread is awake now!" << std::endl;
        x.join();
        y.join();
    }

    // 一个简单的函数，模拟耗时的计算任务
    void static computeValue(std::promise<int> prom) {
        std::cout << "Starting computation in a separate thread..." << std::endl;

        // 模拟耗时操作
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // 计算结果
        int result = 42;

        // 将结果存储到promise对象中
        prom.set_value(result);
    }

    int threadTest2() {
        // 创建一个promise对象
        std::promise<int> prom;

        // 获取与promise关联的future对象
        std::future<int> fut = prom.get_future();

        // 在一个新线程中启动计算任务
        std::thread t(computeValue, std::move(prom));

        std::cout << "Main thread is waiting for the result..." << std::endl;

        // 在主线程中等待计算完成并获取结果
        int result = fut.get(); // 阻塞等待，直到promise设置值

        std::cout << "Computation result: " << result << std::endl;

        // 等待子线程结束
        t.join();

        return 0;
    }
};

#endif //THREAD_H
