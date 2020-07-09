cmake_minimum_required(VERSION 3.16)
project(lab_15)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(lab_15 smoke_test.cpp)