//
// Created by Vacant lot on 2025/4/1.
//
#include <functional>
#include <iostream>
#include <vector>
#include "blockingqueue/bqtest2.h"
#include <thread>

template<class T>
class class1 {
public:
    typedef T::iterator iterator;
    // typedef typename T::iterator iterator;
};

class A {
    public:
    typedef A* iterator; ;
};
int main() {

    class1<A> a;
    return 0;
}

