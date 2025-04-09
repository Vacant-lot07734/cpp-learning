//
// Created by Vacant lot on 2025/4/6.
//
#pragma once
#include <iostream>

class A {
public:
    int *a;
    A() {
        a = new int;
    }

    ~A() {
        std::cout << "A::~A()" << std::endl;
    }
};

void sp_test1() {
    // A a1;
    // 错误管理栈对象，a1是栈对象
    // 智能指针出作用域，开始销毁对象
    // 1. 调用其析构函数 a1->A::~A();
    // 2. delete a1; 底层可能调用malloc释放内存，报错
    // std::shared_ptr<A> p(&a1);
    A* a2 = new A();
    std::shared_ptr<A> p(a2);
}
void sp_test2() {
    A* a1 = new A();
    std::shared_ptr<A> p(a1);
    std::shared_ptr<A> p2(p);
    // 永远不要将同一个裸指针传入多个 SharedPtr<T> 构造函数
    // 会导致每个智能指针都以为自己是唯一拥有者，造成重复释放内存
    // std::shared_ptr<A> p3(a1);
}
