cmake_minimum_required(VERSION 3.16)

project(<project_name>)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_library(<project_name>_lib ${LIB_SOURCES})
target_include_directories(<project_name>_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(<project_name> main.cpp)
target_link_libraries(<project_name> PRIVATE <project_name>_lib)

add_executable(<project_name>_tests ${TEST_SOURCES})
target_include_directories(
  <project_name>_tests
    PUBLIC
      ${CMAKE_SOURCE_DIR}/tests/include
)
target_link_libraries(<project_name>_tests PRIVATE <project_name>_lib gtest gtest_main)
