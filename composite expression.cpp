#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include "composite expression.h"

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

composite_expression:: composite_expression(const std::string str){
    auto tokens = split(str, ' ');
    for (auto token : tokens){
        expression.push_back(Token (token));
    }
}

composite_expression:: composite_expression(const composite_expression& other){
    expression = other.expression;
}

composite_expression composite_expression::get_reverse_polish_notation() {
    composite_expression rpn;
    composite_expression stack;
    Token stack_top;
    Token operand;
    int stack_top_priority;
    int operation_priority;
    for (auto operand : expression){
        if (operand.get_stack_priority() == -1) rpn.expression.push_back(operand);
        else
            if (stack.expression.empty())
                stack.expression.push_back(operand);
            else{
                stack_top_priority = stack.expression.back().get_stack_priority();
                operation_priority = operand.get_stack_priority();
                stack_top = stack.expression.back();
                if (operation_priority > stack_top_priority) {
                    stack.expression.push_back(operand);
                }
                else {
                    while (operation_priority <= stack_top_priority){
                        rpn.expression.push_back(stack_top);
                        stack.expression.pop_back();
                        stack_top = stack.expression.back();
                        stack_top_priority = stack.expression.back().get_stack_priority();
                    }
                    stack.expression.push_back(operand);
                }
            }

    }
    while (!stack.expression.empty()){
        stack_top = stack.expression.back();
        rpn.expression.push_back(stack_top);
        stack.expression.pop_back();

    }
    return rpn;
}