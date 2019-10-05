cmake_minimum_required(VERSION 3.14)

project(objectPoolTest)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/objectPoolTest.cpp)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/objectPool/include
        PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
        gtest
        gmock_main)
add_dependencies(${PROJECT_NAME}
        objectPool)
add_test(NAME AllTests COMMAND ${PROJECT_NAME})