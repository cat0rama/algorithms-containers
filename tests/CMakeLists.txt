cmake_minimum_required(VERSION 3.20)

project(UNIT_TESTS)

add_subdirectory(${PROJECT_SOURCE_DIR}/../vendor/googletest ${CMAKE_CURRENT_BINARY_DIR}/tests)

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

enable_testing()

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} gtest gtest_main)

add_test(${PROJECT_NAME} ${PROJECT_NAME})

include_directories(../include PRIVATE)