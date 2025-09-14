cmake_minimum_required(VERSION 3.16)

project(lab01)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_library(lab01_lib ${LIB_SOURCES})
target_include_directories(lab01_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(lab01 main.cpp)
target_link_libraries(lab01 PRIVATE lab01_lib)

add_executable(lab01_tests ${TEST_SOURCES})
target_include_directories(lab01_tests PUBLIC ${CMAKE_SOURCE_DIR}/tests/include)
target_link_libraries(lab01_tests PRIVATE lab01_lib gtest gtest_main)
