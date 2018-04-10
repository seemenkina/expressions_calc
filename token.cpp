#include <iostream>

#include "token.h"

/* value stack priority:
 *      = - 1
 *      | - 2
 *      & - 3
 *      operand - -1
 */
Token::Token(std::string s) {
    name = s;
    char c = s[0];
    switch (c) {
        case '=': {
            stack_priority = 1;
            token_type = kTokenAssign;
            break;
        }
        case '|': {
            stack_priority = 2;
            token_type = kTokenOr;
            break;
        }
        case '&': {
            stack_priority = 3;
            token_type = kTokenAnd;
            break;
        }
        default: {
            stack_priority = -1;
            token_type = kTokenConst;
        }
    }
}

TokenType Token::type() const {
    return token_type;
}

int Token::priority() const {
    return stack_priority;
}

std::string Token::get_name() const {
    return name;
}

bool Token::operator<(const Token &other) const {
    return name < other.name;
}

std::ostream &operator<<(std::ostream &out, const Token &source) {
    out << source.name;
    return out;
}

std::istream &operator>>(std::istream &in, Token *destination) {
    std::string buf;
    in >> buf;
    destination = new Token(buf);
    return in;
}

