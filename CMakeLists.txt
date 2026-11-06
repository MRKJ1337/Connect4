cmake_minimum_required(VERSION 3.20)

project(c4 LANGUAGES CXX)

set(EXECUTABLE_NAME c4)
set(EXECUTABLE_NAME_UNITTEST c4_unittest)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)

set(
    SRCS
    src/engine/engine.cpp
)

set(
    SRCS_GTEST
    ${SRCS}
    src/engine/engine_unittest.cpp
)

set(
    HEADERS
    src/engine/engine.hpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Avoid creating products into useless separate folders like "Debug" or "Release"
# but inside the same directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src/include/googletest EXCLUDE_FROM_ALL)

add_executable(${EXECUTABLE_NAME} ${SRCS} src/main.cpp ${HEADERS})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE)

add_executable(${EXECUTABLE_NAME_UNITTEST} src/main_unittest.cpp ${SRCS_GTEST} ${HEADERS})
target_link_libraries(${EXECUTABLE_NAME_UNITTEST} PRIVATE GTest::gtest_main)
