cmake_minimum_required(VERSION 3.16)

project(classroom)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_library(classroom_lib ${LIB_SOURCES})
target_include_directories(classroom_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(classroom main.cpp)
target_link_libraries(classroom PRIVATE classroom_lib)

add_executable(classroom_tests ${TEST_SOURCES})
target_include_directories(
  classroom_tests
    PUBLIC
      ${CMAKE_SOURCE_DIR}/tests/include
)
target_link_libraries(classroom_tests PRIVATE classroom_lib gtest gtest_main)
