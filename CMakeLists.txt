cmake_minimum_required (VERSION 3.11)
project (BigInt)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (./includes)

add_executable (
    BigInt
    "./src/main.cpp"
    "./tools/algorithm.cpp"
    "./tools/compare.cpp"
    "./tools/initialize.cpp"
    "./tools/iostream.cpp"
)
