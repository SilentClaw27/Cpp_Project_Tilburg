cmake_minimum_required(VERSION 3.20)
project(GUITest)

set(CMAKE_CXX_STANDARD 14)

add_executable(GUITest main.cpp snake.h grid.h functions.h fruit.h)
