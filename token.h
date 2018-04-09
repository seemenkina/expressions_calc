#ifndef SKB_PROJECT_TOKEN_H
#define SKB_PROJECT_TOKEN_H

#include <string.h>

class Token{
private:
    std::string name;
    int stack_priority;
public:
    /* value stack priority:
     *      = - 1
     *      | - 2
     *      & - 3
     *      operand - -1
     *      unknown - 0
     */
    Token(std::string s = ""){
        name = s;
        char c = s[0];
        switch(c){
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

    Token(const Token& other){
        name = other.name;
        stack_priority = other.stack_priority;
    }

    int get_stack_priority() const{
        return stack_priority;
    }

    std::string get_name() const{
        return name;
    }

    bool operator < (const Token& other) const {
        return name < other.name;
    }

    friend std::ostream& operator << (std::ostream &out, const Token& source){
        out << source.name;
        return out;
    }

    friend std::istream& operator >> (std::istream &in, Token *destination) {
        std::string buf;
        in >> buf;
        destination = new Token(buf);
        return in;
    }
};

#endif //SKB_PROJECT_TOKEN_H
