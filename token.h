#ifndef SKB_PROJECT_TOKEN_H
#define SKB_PROJECT_TOKEN_H

#include <string.h>
#include <iostream>

class Token{
private:
    std::string name;
    int stack_priority;
public:
    Token(std::string s = "");
    Token(const Token& other);
    int get_stack_priority() const;
    std::string get_name() const;
    bool operator < (const Token& other) const;
    friend std::ostream& operator << (std::ostream &out, const Token& source);
    friend std::istream& operator >> (std::istream &in, Token *destination);
};

#endif //SKB_PROJECT_TOKEN_H
