cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
file(GLOB SRC_FILES "src/*.cpp")

# 创建库
add_library(MyLibrary SHARED ${SRC_FILES})
target_include_directories(MyLibrary PUBLIC include)

# 启用测试（只在顶层调用一次）
enable_testing()

# 添加测试子目录
add_subdirectory(tests)

