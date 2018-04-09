# cmake_minimum_required(VERSION <specify CMake version here>)
project(skb_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(skb_project main.cpp "composite expression.cpp" "composite expression.h" token.h)