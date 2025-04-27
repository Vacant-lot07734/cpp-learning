#include <iostream>
#include <threadpool/threadpool.h>
#include <blockingqueue/blockingqueue.tpp>

int main() {
    std::cout << "test";
    using Task = std::function<void()>;
    std::unique_ptr<BlockQueue<Task>> q(new BlockQueue<Task>(2));
    std::unique_ptr<MyThreadPool> ptr(new MyThreadPool(2, 4, std::chrono::milliseconds(2),
        std::move(q), nullptr));
}
