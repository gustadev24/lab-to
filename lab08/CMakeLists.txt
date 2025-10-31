cmake_minimum_required(VERSION 3.16)

project(Templates)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_library(Templates_lib ${LIB_SOURCES})
target_include_directories(Templates_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(Templates main.cpp)
target_link_libraries(Templates PRIVATE Templates_lib)

add_executable(Templates_tests ${TEST_SOURCES})
target_include_directories(
  Templates_tests
    PUBLIC
      ${CMAKE_SOURCE_DIR}/tests/include
)
target_link_libraries(Templates_tests PRIVATE Templates_lib gtest gtest_main)
