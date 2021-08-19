cmake_minimum_required(VERSION 3.16.3)
project(Calculator VERSION 1.0.0)

add_subdirectory(mathops)
add_subdirectory(disp)

add_executable(calc main.cpp)
target_link_libraries(calc PRIVATE mathops disp)
