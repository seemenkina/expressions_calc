#include <map>
#include <string>
#include <vector>

#include "token.h"
#include "composite_expression.h"
#include "expression_calculator.h"

bool ExpressionCalculator::store_token_value(Token t, int v) {
    auto check_pair = dictionary.insert(std::make_pair(t, v));
    return check_pair.second;
}

void ExpressionCalculator::queue_calculate(std::queue <CompositeExpression> &RPN) {
    // Должны обработать не меньше, чем было в очереди на данной
    // итерации. Храним отдельно, т.к. невычисленные элементы
    // остаются в очереди.
    int exp_to_process = RPN.size();
    while (!RPN.empty() && (exp_to_process > 0)) {
        auto elem = RPN.front();
        int result = elem.calculate_rpn_expression(dictionary);
        if (result == VALUE_UNKNOWN) {
            // Вычисление на данный момент невозможно, поэтому
            // выражение добавляется в конец очереди.
            RPN.push(elem);
        } else {
            // Все ок. Сохраняем результат выражения.
            auto result_token = elem.get_first_token();
            dictionary[result_token] = result;
        }
        RPN.pop();
        exp_to_process--;
    }
}

inline Token get_result_token(const CompositeExpression exp) {
    // На уровне спецификации сложного выражения, первым токеном всегда будет
    // токен, содержащий результат выражения.
    return exp.get_first_token();
}

bool ExpressionCalculator::add_simple_expression(std::string key, int value) {
    return store_token_value(Token(key), value);
}

bool ExpressionCalculator::add_composite_expression(std::string exp) {
    auto ce = CompositeExpression(exp);
    composite_expressions.push_back(ce);
    return store_token_value(get_result_token(ce), VALUE_UNKNOWN);
}

std::vector<int> ExpressionCalculator::solve() {
    std::queue <CompositeExpression> RPN;
    for (auto exp: composite_expressions) {
        RPN.push(CompositeExpression(exp.get_reverse_polish_notation()));
    }

    int last_size = -1;
    while (!RPN.empty()) {
        queue_calculate(RPN);
        if (last_size == RPN.size()) break;
        last_size = RPN.size();
    }

    std::vector<int> result;
    for (auto exp: composite_expressions) {
        auto result_token = get_result_token(exp);
        result.push_back(dictionary[result_token]);
    }
    return result;
}
