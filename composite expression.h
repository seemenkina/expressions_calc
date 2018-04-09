#ifndef SKB_PROJECT_COMPOSITE_EXPRESSION_H
#define SKB_PROJECT_COMPOSITE_EXPRESSION_H

#include "token.h"
#include <vector>
#include <string.h>
#include <map>

typedef std::map<Token, int> DictionaryMap;

class composite_expression{
private:
    std::vector<Token> expression;
public:
    composite_expression(std::string s = "");
    composite_expression(const composite_expression& other);

    Token get_first_token();

    composite_expression get_reverse_polish_notation();

    int calculate_rpn_expression(DictionaryMap& dictionary) const;
    friend std::ostream& operator << (std::ostream &out, const composite_expression& source){
        for (auto i: source.expression){
            out << i << ' ';
        }
        return out;
    }
};

#endif //SKB_PROJECT_COMPOSITE_EXPRESSION_H
