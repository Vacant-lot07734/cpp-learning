cmake_minimum_required(VERSION 3.30)
project(cpp-learning)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
file(GLOB SRC_LIST "src/**/*.cpp")
#aux_source_directory(./src SRC_LIST)
add_executable(main ${SRC_LIST} ./src/main.cpp)