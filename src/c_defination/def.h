//
// Created by Vacant lot on 2025/3/30.
//

#ifndef DEF_H
#define DEF_H
#include <iostream>
#include <ostream>
class Def {
    public:
    // c++已经显式inline
    inline void func1(int a, int b) {
        std::cout << "func1" << a << " " << b << std::endl;
    }
    void func2(int a, int b);
};

#endif //DEF_H
