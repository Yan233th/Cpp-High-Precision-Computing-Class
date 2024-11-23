cmake_minimum_required (VERSION 3.11)
project (BigInt)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

include_directories (./includes)

add_compile_definitions (CMAKE)

add_executable (BigInt ./src/main.cpp)
