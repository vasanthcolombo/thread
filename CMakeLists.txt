cmake_minimum_required(VERSION 3.14)
project(vlib)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB SOURCE thread/src/*.cpp)
add_executable(vthread
        ${SOURCE})

target_include_directories(vthread
        PRIVATE thread/include)