//
// Created by Vacant lot on 2025/3/27.
#include <random>
#include <ctime>
int randint(int min, int max) {
    std::default_random_engine e(time(0));
    std::uniform_int_distribution<int> u(min, max);
    return u(e);
}
