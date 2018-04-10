#ifndef SKB_PROJECT_TOKEN_H
#define SKB_PROJECT_TOKEN_H

#include <string>
#include <iostream>

typedef enum {
    kTokenConst = -1,
    kTokenAssign = 1,
    kTokenOr = 2,
    kTokenAnd = 3,
} TokenType;

class Token {
private:
    std::string name;
    int stack_priority;
    TokenType token_type;
public:
    Token(std::string s = "");

    int priority() const;

    TokenType type() const;

    std::string get_name() const;

    bool operator<(const Token &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Token &source);

    friend std::istream &operator>>(std::istream &in, Token *destination);
};

#endif //SKB_PROJECT_TOKEN_H
