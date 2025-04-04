//
// Created by Vacant lot on 2025/4/4.
//

#ifndef FUNC_PTR_H
#define FUNC_PTR_H
#include <iostream>
#include <ostream>
// 函数类型是 void (int)
void func1(int x) {
    std::cout << "func1(" << x << ")" << std::endl;
}

void function_test() {
    // 函数指针就是函数名
    void (*pf)(int) = func1;
    pf(1);

    typedef void (*Pf2)(int);
    Pf2 pf2= func1;
    pf2(1);

    using Pf3 = void (*)(int);
    Pf3 pf3= func1;
    pf3(1);
}
#endif //FUNC_PTR_H
