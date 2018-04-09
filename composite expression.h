#ifndef SKB_PROJECT_COMPOSITE_EXPRESSION_H
#define SKB_PROJECT_COMPOSITE_EXPRESSION_H

#include "token.h"
#include <vector>
#include <string.h>

class composite_expression{
private:
    std::vector<Token> expression;
public:
    composite_expression(std::string s = "");
    composite_expression(const composite_expression& other);



    composite_expression get_reverse_polish_notation();

    friend std::ostream& operator << (std::ostream &out, const composite_expression& source){
        for (auto i: source.expression){
            out << i << ' ';
        }
        return out;
    }
};

#endif //SKB_PROJECT_COMPOSITE_EXPRESSION_H
