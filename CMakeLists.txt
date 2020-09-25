cmake_minimum_required(VERSION 3.14)
project(vlib)

set(CMAKE_CXX_STANDARD 17)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# Thread
FILE(GLOB THREAD_SOURCE
        thread/src/*.cpp)
add_executable(thread
        ${THREAD_SOURCE})
target_include_directories(thread
        PRIVATE thread/include)

# ObjectPool
FILE(GLOB OBJECTPOOL_SOURCE
        objectPool/src/main.cpp)
add_executable(objectPool
        ${OBJECTPOOL_SOURCE})
target_include_directories(objectPool
        PRIVATE objectPool/include)

# PRODUCER_CONSUMER
FILE(GLOB PRODUCERCONSUMER_SOURCE
        thread/src/*.cpp
        producerConsumer/src/*.cpp)
add_executable(producerConsumer
        ${PRODUCERCONSUMER_SOURCE})
target_include_directories(producerConsumer
        PRIVATE producerConsumer/include
        PRIVATE thread/include)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/objectPool/test)
#add_subdirectory(${CMAKE_SOURCE_DIR}/producerConsumer)
#add_dependencies(objectPool
#        objectPoolTest)

add_executable(ringbuffer
        producerConsumer/ringbuffer.cpp)

# UTIl CLASSES
FILE(GLOB UTIL_SOURCES
        util/src/*.cpp
        util/main.cpp
        thread/src/*.cpp)

add_executable(utilMain
        ${UTIL_SOURCES})
target_include_directories(utilMain
        PRIVATE util/include
        PRIVATE thread/include)

add_executable(game
        game.cpp)

add_executable(scratch
        scratch.cpp)

add_executable(scratch2
        scratch2.cpp)