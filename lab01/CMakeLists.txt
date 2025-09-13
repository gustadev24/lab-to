cmake_minimum_required(VERSION 3.16)

project(lab01)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(lab01 src/main.cpp ${SOURCES})

target_include_directories(lab01
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
