cmake_minimum_required(VERSION 3.17)
project(NES)

set(CMAKE_CXX_STANDARD 14)

add_executable(NES main.cpp Bus.cpp Bus.h CPU.cpp CPU.h Utils.h)