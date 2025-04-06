//
// Created by Vacant lot on 2025/4/6.
//
#include <iostream>
class A{
    public:
		int a[10];
        ~A(){
                  std::cout<<"A::~A()"<<std::endl;}
};

void sp_test(){
  A a1;
  std::shared_ptr<A> p(&a1);
  std::shared_ptr<A> p2(&a1);
  }