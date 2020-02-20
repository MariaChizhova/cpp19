cmake_minimum_required(VERSION 3.13)
project(lab_11)

include_directories(include/bin_manip.h include/employees.h)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab_11 src/main.cpp src/bin_manip.cpp src/employees.cpp)