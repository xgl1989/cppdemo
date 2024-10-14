cmake_minimum_required(VERSION 3.10)
#-----------------------------------------
# 添加测试源文件
#file(GLOB TEST_SRCS "test_*.cpp")

# 创建测试可执行文件
#add_executable(MyLibraryTests ${TEST_SRCS})
#target_link_libraries(MyLibraryTests MyLibrary)

# 添加测试到 CTest（不需要再次调用 enable_testing）
#add_test(NAME MyTest COMMAND MyLibraryTests)
#-------------------------------------------


# 收集所有 test_*.cpp 文件
file(GLOB TEST_SRCS "test_*.cpp")

# 循环处理每个 .cpp 文件
foreach(SRC ${TEST_SRCS})
    # 获取不带路径和扩展名的文件名
    get_filename_component(TEST_NAME ${SRC} NAME_WE)

    # 创建可执行文件
    add_executable(${TEST_NAME} ${SRC})

    # 链接库（如果需要）
    target_link_libraries(${TEST_NAME} MyLibrary)

    # 添加测试
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()


#-------------------------------------------------------------------------------
# 假设 test1.cpp, test2.cpp, test3.cpp 分别编译成三个不同的可执行文件
#add_executable(test1 test1.cpp)
#add_executable(test2 test2.cpp)
#add_executable(test3 test3.cpp)

# 分别为每个可执行文件添加测试
#add_test(NAME Test1 COMMAND test1)
#add_test(NAME Test2 COMMAND test2)
#add_test(NAME Test3 COMMAND test3)


# 假设 test1.cpp, test2.cpp, test3.cpp 都链接成一个可执行文件 MyLibraryTests
#file(GLOB TEST_SRCS "test_*.cpp")
#add_executable(MyLibraryTests ${TEST_SRCS})

# 为这个可执行文件添加测试
#add_test(NAME MyTest COMMAND MyLibraryTests)
