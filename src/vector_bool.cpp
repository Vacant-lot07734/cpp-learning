//
// Created by Vacant lot on 2025/4/1.
//
#include <iostream>
#include <vector>
int func() {
    // 并非真正的vector容器，事实上压缩存储了，每个元素只占一位
    std::vector<bool> x = {true, true, false, true, false,true, true, true, false, true};
    // reference
    auto y = x[1];
    // 隐式类型转换
    bool z = x[0];
    // bool &tmp = x[0];   //错误，不能编译，对于引用来说，因为c[0]不是一个左值
    // bool *p = &x[0];    //错误，不能编译，因为无法将一个临时量地址给绑定到指针
    return 0;
}//1101 0111 01