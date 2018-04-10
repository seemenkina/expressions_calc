add_library(rpn STATIC token.cpp composite_expression.cpp expression_calculator.cpp)

target_include_directories(rpn PUBLIC ${PROJECT_SOURCE_DIR}/include/rpn)