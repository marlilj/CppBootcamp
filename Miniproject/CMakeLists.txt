cmake_minimum_required(VERSION 3.16.3)
project(sudoku VERSION 0.0.1)
include_directories(include)
add_executable(sudoku src/main.cpp src/solver.cpp src/printer.cpp src/reader.cpp src/brute_force.cpp include/variable_definitions.h)