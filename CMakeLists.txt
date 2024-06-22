cmake_minimum_required(VERSION 3.28)
project(cppdemo)

set(CMAKE_CXX_STANDARD 11)

add_library(cppdemo SHARED library.cpp)
