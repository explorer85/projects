cmake_minimum_required(VERSION 3.5)

project(typelists LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(typelists main.cpp visitor.h visitor.cpp typelist.h)
