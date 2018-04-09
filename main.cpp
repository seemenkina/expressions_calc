#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <queue>

#include "composite expression.h"

int main(int argc, char* argv[]){

    std::ifstream input_file;
    std::ofstream output_file;

    std::string name_input_file = "input.txt";
    std::string name_output_file = "output.txt";


    input_file.open(name_input_file);

    if (!input_file.good()){
        std:: cout << "Exception opening file: " << name_input_file << '\n';
        std::exit(1);
    }

    output_file.open(name_output_file);

    if (!output_file.good()){
        std:: cout << "Exception opening file: " << name_output_file << '\n';
        std::exit(1);
    }

    int N;
    int M;

    input_file >> N >> M;

    std::map<Token, int> dictionary;
    int value;
    std::string buf;

    for (int i = 0; i < N; i++){

        input_file >> buf >> value;
        auto check_pair = dictionary.insert(std::pair<Token,int>(Token(buf), value));
        if (!(check_pair.second)) {
            std::cout << "not ok";
        }
        output_file << check_pair.first->first << " " << check_pair.first->second <<'\n';
    }

    std::vector<composite_expression> expressions;
    std::string exp;
    std::getline(input_file, exp); // добиваю последнюю строку из предыдущего цикла

    while(!input_file.eof()) {
        std::getline(input_file, exp);
        exp.erase(exp.find_last_not_of(" \n\r\t")+1);
        expressions.push_back(composite_expression(exp));
    }

    std::queue<composite_expression> RPN;
    for (auto i: expressions){
        output_file << i << '\n';
        RPN.push(composite_expression(i.get_reverse_polish_notation()));
    }


    std::queue<composite_expression> b = RPN;
    while(!b.empty()) {
        output_file << b.front() << " " <<b.size() << '\n';
        b.pop();
    }


    return 0;
}