cmake_minimum_required(VERSION 3.24)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project2 "src/main.cpp" "src/tga.h" src/main.cpp others.cpp)
