cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
file(GLOB SRC_FILES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# 创建库
add_library(MyLibrary SHARED ${SRC_FILES})
target_include_directories(MyLibrary PUBLIC include)

# 启用测试（只在顶层调用一次）
enable_testing()

# 添加测试子目录
add_subdirectory(tests)

# 设置安装目录
set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include")

# 安装库文件
install(TARGETS MyLibrary
        LIBRARY DESTINATION ${INSTALL_DIR}
        ARCHIVE DESTINATION ${INSTALL_DIR}
        RUNTIME DESTINATION ${INSTALL_DIR})

# 安装头文件

install(FILES ${HEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR})



# 创建卸载target
if(NOT TARGET uninstall)

    # 利用前面的Uninstall.cmake.in文件自动生成Uninstall.cmake
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/Uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake"
            IMMEDIATE @ONLY)

    # 通过add_custom_target创建一个自定义构建目标的命令
    # 自定义目标可以在构建时被执行，但不会产生实际的构建输出。
    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake)

endif()

