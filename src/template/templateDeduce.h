//
// Created by Vacant lot on 2025/4/3.
//

#ifndef TEMPLATEDEDUCE_H
#define TEMPLATEDEDUCE_H
#include <iostream>

#endif //TEMPLATEDEDUCE_H
template<typename T1, typename T2>
void func1(T1 x, T2 y) {
    std::cout << "最普通版本" << std::endl;
    std::cout << x << " " << y << std::endl;
}

template<typename T1>
void func1(T1 x, T1 y) {
    std::cout << "偏特化版本 1" << std::endl;
    std::cout << x << " " << y << std::endl;
}

template<>
inline void func1(int &x, int &y) {
    std::cout << "全特化版本 2" << std::endl;
    std::cout << x << " " << y << std::endl;
}

template<>
inline void func1(int x, int y) {
    std::cout << "全特化版本 3" << std::endl;
    std::cout << x << " " << y << std::endl;
}

template<>
inline void func1(int &&x, int &&y) {
    std::cout << "全特化版本 4" << std::endl;
    std::cout << x << " " << y << std::endl;
}



void templateDeduceTest() {
    func1(1, 2.9);
    func1(1.2, 2.9);
    //形参的右值引用（int&&）仅在模板参数推导时才有特殊的完美转发（universal reference）行为，
    //而在函数特化中，它只是普通的右值引用！
    func1(1, 2); // 全特化版本3
    int *x = new int(2);
    int *y = new int(2);
    func1(x, y);
}
