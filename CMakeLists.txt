cmake_minimum_required(VERSION 3.14)
project(Thread)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB SOURCE src/*.cpp)
add_executable(Thread
        ${SOURCE})

include_directories(include)