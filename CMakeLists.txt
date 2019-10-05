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

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/objectPool/test)
#add_dependencies(objectPool
#        objectPoolTest)
add_executable(scratch
        C:/Users/vasan/.CLion2019.2/config/scratches/scratch.cpp)
