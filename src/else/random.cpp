//
// Created by Vacant lot on 2025/3/27.
#include <random>
#include <ctime>
int randint(int min, int max) {
    // 不能直接放在头文件
    // time是一个运行时函数调用，返回当前时间戳。由于它不是常量表达式（constexpr），不能用于静态初始化
    std::default_random_engine e(time(nullptr));
    std::uniform_int_distribution<int> u(min, max);
    std::uniform_real_distribution<double> uf(min, max);
    return u(e);
}
