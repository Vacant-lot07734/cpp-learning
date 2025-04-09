//
// Created by Vacant lot on 2025/3/25.
//
#pragma once
#include <iostream>

template<typename T, typename U = void>
class TemplateTest {
public:
    TemplateTest(T a) {
        std::cout << a << std::endl;
    }
};

template<>
class TemplateTest<int> {
public:
    TemplateTest(int a) {

        std::cout <<"int"<< a << std::endl;
    }
};
