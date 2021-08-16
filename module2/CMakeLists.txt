cmake_minimum_required(VERSION 3.16.3)
project(Calculator VERSION 1.0.0)

add_library(mathops add.cpp divide.cpp)
add_library(disp print.cpp)

add_executable(calc main.cpp)

target_link_libraries(calc mathops disp)
