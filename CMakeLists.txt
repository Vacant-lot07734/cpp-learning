cmake_minimum_required(VERSION 3.30)
project(cpp-learning)

set(CMAKE_CXX_STANDARD 23)

# 所有子目录里的头文件都能找到, include时需要加上子路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 收集源文件
file(GLOB_RECURSE SRC_FILES
        "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
)
# 生成可执行文件
add_executable(MyProject ${SRC_FILES})


# 分模块编译
#modular_project/
#├── CMakeLists.txt          # 总入口
#├── src/
#│   ├── CMakeLists.txt      # 子目录自己的CMake配置
#│   ├── main.cpp
#│   ├── foo.cpp
#│   └── foo.h

# 总cmakelist.txt:
# add_subdirectory(src) # 加载src目录
# add_executable()
# target_link_libraries() # 链接

# src/cmakelist.txt:
# add_library() # 生成库，默认static，shared为动态
# target_include_directories() # 现代写法，推荐使用，不会污染，有传递性