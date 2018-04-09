#include <stdio.h>
#include <iostream>
#include <fstream>
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

Token composite_expression:: get_first_token(){
    return expression.front();
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


int calc_operation(int op1, int op2, const Token& elem){
    if (elem.get_stack_priority() == 1){
        return op2;
    }
    if (elem.get_stack_priority() == 2){
        if ((op1 == -1) || (op2 == -1)){
            if ((op1 == 0) || (op2 == 0))
                return -1;
            if ((op1 == 1) || (op2 == 1))
                return 1;
            else
                return -1;
        }
        else
            return op1 | op2;
    }

    if (elem.get_stack_priority() == 3){
        if ((op1 == -1) || (op2 == -1)){
            if ((op1 == 0) || (op2 == 0))
                return 0;
            else
                return -1;
        }
        else
            return op1 & op2;
    }
}

int composite_expression:: calculate_rpn_expression(DictionaryMap& dictionary) const{
    std::vector<int> stack_operation;
    for(auto elem : expression){
        if (elem.get_stack_priority() == -1) {
            std::string buf = elem.get_name();
            DictionaryMap:: iterator it = dictionary.find(buf);
            if( it != dictionary.end())
                stack_operation.push_back(dictionary[buf]);
            else
                stack_operation.push_back(-1);
        }
        else {
            int op2 = stack_operation.back();
            stack_operation.pop_back();
            int op1 = stack_operation.back();
            stack_operation.pop_back();
            int anw = calc_operation(op1, op2, elem);
            stack_operation.push_back(anw);
        }
    }
    int answer = stack_operation.back();
    stack_operation.pop_back();
    return answer;
}

