//
// Created by Vacant lot on 2025/4/3.
//

#ifndef TEST2_H
#define TEST2_H

#endif //TEST2_H
#include <iostream>
#include <utility>

template<typename T>
void process2(T &x) {
    std::cout << "lvalue processed: " << x << std::endl;
}

template<typename T>
void process2(T &&x) {
    std::cout << "rvalue processed: " << x << std::endl;
}

// 会调用第二个重载版本
// std::forward<T>(arg)不是具名变量，是一个表达式非左值，会匹配第二个重载，因为第二个重载接受参数为右值
template<typename T>
void wrapper2(T&& arg) {
    process2(myforward<T>(std::forward<T>(arg)));
}

int test2() {
    int x = 42;
    int& y = x;
    wrapper2(x);
    wrapper2(y);
    std::cout<<"--------\n";

    int &&z = 12;
    wrapper2(1);
    wrapper2(std::move(x));
    wrapper2(z);//wrapper2中T推导为 int&，因为右值引用是左值
    return 0;
}