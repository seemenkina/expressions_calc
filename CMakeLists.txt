# cmake_minimum_required(VERSION <specify CMake version here>)
project(skb_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(skb_project main.cpp "composite_expression.cpp" "composite_expression.h" token.h token.cpp expression_calculator.h expression_calculator.cpp)