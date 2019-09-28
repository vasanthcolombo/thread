cmake_minimum_required(VERSION 3.14)
project(vlib)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB THREAD_SOURCE
        thread/src/*.cpp)
add_executable(thread
        ${THREAD_SOURCE})
target_include_directories(thread
        PRIVATE thread/include)

FILE(GLOB OBJECTPOOL_SOURCE
        objectPool/src/main.cpp)
add_executable(objectPool
        ${OBJECTPOOL_SOURCE})
target_include_directories(objectPool
        PRIVATE objectPool/include)