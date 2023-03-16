PROJECT(Containers)

SET(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CONTAINERS_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} main.cpp
    ${CONTAINERS_HEADERS}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
