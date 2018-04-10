#include <string.h>
#include <iostream>

#include "token.h"

/* value stack priority:
 *      = - 1
 *      | - 2
 *      & - 3
 *      operand - -1
 *      unknown - 0
 */
Token:: Token(std::string s) {
    name = s;
    char c = s[0];
    switch (c) {
        case '=': {
            stack_priority = 1;
            break;
        }
        case '|': {
            stack_priority = 2;
            break;
        }
        case '&': {
            stack_priority = 3;
            break;
        }
        default:
            stack_priority = -1;
    }
}

Token:: Token(const Token &other) {
    name = other.name;
    stack_priority = other.stack_priority;
}

int Token:: get_stack_priority() const {
    return stack_priority;
}

std::string Token:: get_name() const {
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

