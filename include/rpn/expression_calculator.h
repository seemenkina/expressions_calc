#ifndef SKB_PROJECT_EXPRESSION_CALCULATOR_H
#define SKB_PROJECT_EXPRESSION_CALCULATOR_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <queue>

#include "token.h"
#include "composite_expression.h"


class ExpressionCalculator {
private:
    DictionaryMap dictionary;
    std::vector <CompositeExpression> composite_expressions;

    bool store_token_value(Token t, int v);

    void queue_calculate(std::queue <CompositeExpression> &RPN);

public:
    bool add_simple_expression(std::string key, int value);

    bool add_composite_expression(std::string exp);

    std::vector<int> solve();
};

#endif //SKB_PROJECT_EXPRESSION_CALCULATOR_H
