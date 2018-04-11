#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdexcept>

#include "composite_expression.h"


/***/
template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector <std::string> split(const std::string &s, char delim) {
    std::vector <std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

/***/

CompositeExpression::CompositeExpression(const std::string str) {
    auto tokens = split(str, ' ');
    for (auto token : tokens) {
        expression.push_back(Token(token));
    }
}

Token CompositeExpression::get_first_token() const {
    return expression.front();
}

CompositeExpression CompositeExpression::get_reverse_polish_notation() {
    CompositeExpression rpn;
    std::vector<Token> stack;
    for (auto operand : expression) {
        if (operand.priority() == -1) 
            rpn.expression.push_back(operand);
        else if (stack.empty())
            stack.push_back(operand);
        else {
            Token stack_top = stack.back();
            if (operand.priority() > stack_top.priority()) {
                stack.push_back(operand);
            } else {
                while (operand.priority() <= stack_top.priority()) {
                    rpn.expression.push_back(stack_top);
                    stack.pop_back();
                    stack_top = stack.back();
                }
                stack.push_back(operand);
            }
        }
    }
    while (!stack.empty()) {
        Token stack_top = stack.back();
        rpn.expression.push_back(stack_top);
        stack.pop_back();
    }
    return rpn;
}

int calc_operation(int op1, int op2, const Token &elem) {
    if (elem.type() == kTokenAssign) {
        return op2;
    }
    if (elem.type() == kTokenOr) {
        if ((op1 == 1) || (op2 == 1)) return 1;
        if ((op1 == 0) && (op2 == 0)) return 0;
        return VALUE_UNKNOWN;
    }
    if (elem.priority() == kTokenAnd) {
        if ((op1 == 1) && (op2 == 1)) return 1;
        if ((op1 == 0) || (op2 == 0)) return 0;
        return VALUE_UNKNOWN;
    }
    throw std::invalid_argument("Unknown operation.");
}

int CompositeExpression::calculate_rpn_expression(DictionaryMap &dictionary) const {
    std::vector<int> stack;
    for (auto elem : expression) {
        if (elem.type() == kTokenConst) {
            DictionaryMap::iterator it = dictionary.find(elem);
            if (it != dictionary.end())
                stack.push_back(dictionary[elem]);
            else
                stack.push_back(VALUE_UNKNOWN);
        } else {
            int op2 = stack.back();
            stack.pop_back();
            int op1 = stack.back();
            stack.pop_back();
            int result = calc_operation(op1, op2, elem);
            stack.push_back(result);
        }
    }
    if (stack.size() != 1)
        throw std::invalid_argument("Incorrect RPN.");
    return stack.back();
}

std::ostream &operator<<(std::ostream &out, const CompositeExpression &source) {
    for (auto i: source.expression) {
        out << i << ' ';
    }
    return out;
}

