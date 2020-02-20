cmake_minimum_required(VERSION 3.10)
project(hw_02)
project(test_hw_02)

include_directories(include)

add_executable(hw_02 src/main.cpp src/Board.cpp src/StdioBoardView.cpp)
add_executable(test_hw_02 test/BoardTest.cpp test/Test.cpp include/Test.h test/test.cpp src/Board.cpp src/StdioBoardView.cpp)
