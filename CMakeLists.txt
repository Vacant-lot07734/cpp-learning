cmake_minimum_required(VERSION 3.30)
project(leetcode)

set(CMAKE_CXX_STANDARD 23)

add_executable(main src/template/sfinae.cpp
        src/template/templateTest.h
        src/template/templateTest.cpp
        src/random.cpp
        src/c_defination/def.h
        src/c_defination/def.cpp
        src/vector_bool.cpp
        src/blockingqueue/blockingqueue.tpp
        src/blockingqueue/bqtest.h
        src/main.cpp
        src/perfect_forward/forward.h
        src/perfect_forward/test.h
        src/template/templateDeduce.h
        src/perfect_forward/test2.h
        src/template/templateDeduce2.h
        src/function/func_ptr.h
        src/function/bind.h
        src/function/ref.h
        src/blockingqueue/bqtest2.h
        src/smartpointer/shared_ptr.tpp
)
