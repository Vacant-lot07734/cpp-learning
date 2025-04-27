//
// Created by Vacant lot on 2025/4/23.
//

#ifndef TMP_H
#define TMP_H
#include <type_traits>
// 编译期计算阶乘
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

template<typename T>
void func(){
    std::remove_reference<T>();
}
#endif //TMP_H
