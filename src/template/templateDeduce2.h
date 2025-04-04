//
// Created by Vacant lot on 2025/4/3.
//

#ifndef TEMPLATEDEDECE2_H
#define TEMPLATEDEDECE2_H

#endif //TEMPLATEDEDECE2_H
#include <iostream>
// 重载1：处理左值（T被推导为左值引用类型）
template<typename T>
void func(T& arg) {
    std::cout << "左值重载: " << typeid(T).name() << std::endl;
}

// 重载2：处理右值（T被推导为非引用类型）
template<typename T>
void func(T&& arg) {
    std::cout << "右值重载: " << typeid(T).name() << std::endl;
}
int template_deduce() {
    int x = 42;
    const int y = 100;
    int&& z = 12;
    func(x);        // 左值重载，T = int
    func(y);        // 左值重载，T = const int
    func(42);       // 右值重载，T = int
    func(std::move(x)); // 右值重载，T = int
    func(std::move(z));
    std::cout<<std::type_index(typeid(2.2)).name()<<std::endl;
}


