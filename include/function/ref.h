//
// Created by Vacant lot on 2025/4/4.
//

#ifndef REF_H
#define REF_H
#include<iostream>
#include<functional>


void f(int &n1, int &n2, const int &n3) {
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
    // ++n3; // compile error
}
int f2(int x, int& y) {
    std::cout<<++x<<" "<<++y<<std::endl;
}

//预绑定的参数是以值传递的形式，
//不预绑定的参数要用std::placeholders(占位符)的形式占位，从_1开始，依次递增，
//是以引用传递的形式, 无论绑定的函数本身定义是否是引用
int ref() {
    int n1 = 1, n2 = 2, n3 = 3;

    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));

    n1 = 10;
    n2 = 11;
    n3 = 12;

    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';

    auto f = std::bind(f2, std::placeholders::_1, std::placeholders::_2);
    int x = 10, y = 12;
    f(x, y);
    std::cout<<++x<<" "<<++y<<std::endl;

    return 0;
}
#endif //REF_H
