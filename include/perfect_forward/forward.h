//
// Created by Vacant lot on 2025/4/2.
//

#ifndef FORWARD_H
#define FORWARD_H

#endif //FORWARD_H
#include <type_traits>
#include <iostream>
// 引用折叠
// 如果任一引用为左值引用，则结果为左值引用。否则（即两个都是右值引用）

// 重载1：用于转发左值
template<typename T>
constexpr T &&myforward(typename std::remove_reference<T>::type &arg) noexcept {
    std::cout<<"重载版本一\n";
    return static_cast<T &&>(arg);
}

// 重载2：用于转发右值
template<typename T>
constexpr T &&myforward(typename std::remove_reference<T>::type &&arg) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "myforward: Cannot forward rvalue as lvalue");
    std::cout<<"重载版本二\n";
    return static_cast<T &&>(arg);
}
