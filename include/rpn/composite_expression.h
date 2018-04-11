#ifndef SKB_PROJECT_CompositeExpression_H
#define SKB_PROJECT_CompositeExpression_H

#include <vector>
#include <string>
#include <map>

#include "token.h"

#define VALUE_UNKNOWN -1

typedef std::map<Token, int> DictionaryMap;

class CompositeExpression {
private:
    std::vector <Token> expression;
public:
    CompositeExpression(std::string s = "");

    Token get_first_token() const;

    CompositeExpression get_reverse_polish_notation();

    int calculate_rpn_expression(DictionaryMap &dictionary) const;

    friend std::ostream &operator<<(std::ostream &out, const CompositeExpression &source);
};

#endif //SKB_PROJECT_CompositeExpression_H
