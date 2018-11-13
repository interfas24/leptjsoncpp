cmake_minimum_required(VERSION 2.6)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
project(leptjsoncpp_test)

set(CMAKE_CXX_STANDARD 11)
add_library(leptjsoncpp leptjsoncpp.cpp)
add_executable(leptjsoncpp_test test.cpp)
target_link_libraries(leptjsoncpp_test leptjsoncpp)
