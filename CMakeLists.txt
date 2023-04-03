cmake_minimum_required(VERSION 3.20)

project(Containers)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CONTAINERS_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} main.cpp
    ${CONTAINERS_HEADERS}
)

add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)