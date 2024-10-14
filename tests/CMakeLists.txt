cmake_minimum_required(VERSION 3.10)

# 添加测试源文件
file(GLOB TEST_SRCS "test_*.cpp")

# 创建测试可执行文件
add_executable(MyLibraryTests ${TEST_SRCS})
target_link_libraries(MyLibraryTests MyLibrary)

# 添加测试到 CTest（不需要再次调用 enable_testing）
add_test(NAME MyTest COMMAND MyLibraryTests)