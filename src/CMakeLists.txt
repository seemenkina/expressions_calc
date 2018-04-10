add_subdirectory(rpn)

add_executable(skb_project main.cpp)

target_link_libraries(skb_project rpn)

target_include_directories(skb_project PRIVATE ${PROJECT_SOURCE_DIR}/include/rpn)
