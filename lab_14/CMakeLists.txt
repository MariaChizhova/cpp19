cmake_minimum_required(VERSION 3.10)
project(lab_14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
include_directories(include)

add_executable(lab_14 src/main.cpp include/matrix.h src/matrix.cpp)