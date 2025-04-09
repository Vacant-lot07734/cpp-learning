//
// Created by Vacant lot on 2025/4/2.
//
#pragma once
#include "forward.h"

#include <iostream>

template<typename T>
void process(T &x) {
    std::cout << "lvalue processed: " << x << std::endl;
}

template<typename T>
void process(T &&x) {
    std::cout << "rvalue processed: " << x << std::endl;
}

// 用T&&类型的形参既能绑定右值，又能绑定左值
// 但是注意了：只有发生类型推导的时候，T &&才表示万能引用（如模板函数传参就会经过类型推导的过程
// 否则，表示右值引用

// wrapper 只会调用第一个重载
// 在 wrapper 内部，arg 是具名变量，即使其类型是 T&&，它仍然是左值，只能匹配第一个重载
// arg虽然是左值，但是T被推导为int为例时，可以正确转发右值，当且仅当调用传参为纯右值或std::move语义
template<typename T>
void wrapper(T &&arg) {
    process(myforward<T>(arg));
}

inline void test1() {
    int x = 42;
    int &y = x;
    wrapper(x); // 左值的类型在模板参数中会被视为它本身的引用类型,wrapper中T = int&
    wrapper(y); //wrapper中T = int&
    std::cout << "---------" << std::endl;

    int &&z = 12;
    wrapper(12); //右值会被推断为int类型而不是int&&,wrapper中T = int
    wrapper(std::move(x));//wrapper中T = int
    wrapper(z);// z事实上是左值
    std::cout << "---------" << std::endl;

}
