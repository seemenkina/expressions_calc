#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <queue>

#include "composite expression.h"

typedef std::map<Token, int> DictionaryMap;
typedef std::queue<composite_expression> CEqueue;
typedef std::string String;


int queue_calculate(DictionaryMap& dictionary, CEqueue& RPN, int m_buf){
    int a;
    int exit_queue = m_buf;
    while (!RPN.empty()) {
        auto elem = RPN.front();
        if (exit_queue == 0) return m_buf;
        a = elem.calculate_rpn_expression(dictionary);
        if (a == -1) {
            RPN.push(elem);
            RPN.pop();
            exit_queue --;
            break;
        }
        else{
            String buf = elem.get_first_token().get_name();
            dictionary[buf] = a;
            RPN.pop();
            m_buf --;
            exit_queue --;
        }
    }
    return m_buf;
}

int main(int argc, char* argv[]){

    std::ifstream input_file;
    std::ofstream output_file;

    String name_input_file;
    String name_output_file;

    if( argc == 3 ) {
        name_input_file = argv[1];
        name_output_file = argv[2];
    }
    else {
        std::cout << "Usage: ./cppfile InputFile OutputFile\n";
        std::exit(1);
    }
    input_file.open(name_input_file);

    if (!input_file.good()){
        std:: cout << "Exception opening file: " << name_input_file << '\n';
        std::exit(1);
    }

    output_file.open(name_output_file);

    int N;
    int M;

    input_file >> N >> M;

    DictionaryMap dictionary;
    int value;
    String buf;

    for (int i = 0; i < N; i++){
        input_file >> buf >> value;
        auto check_pair = dictionary.insert(std::pair<Token,int>(Token(buf), value));
        if (!(check_pair.second)) {
            std::cout << "Exception insert pair to dictionary. \n "
                         <<  "Input data do not satisfy the specification. \n";
            std::exit(1);
        }
    }

    DictionaryMap buf_dictionary = dictionary; //словарь только простых высказываний,
                                                    // понадобится для вывода
    String exp;
    std::vector<composite_expression> expressions;
    std::getline(input_file, exp); // добиваю последнюю строку из предыдущего цикла

    while(!input_file.eof()) {
        std::getline(input_file, exp);
        exp.erase(exp.find_last_not_of(" \n\r\t")+1);
        expressions.push_back(composite_expression(exp));

        auto init_pair = expressions.back().get_first_token();
        auto check_pair = dictionary.insert(std::pair<Token,int>(init_pair, -1));
        if (!(check_pair.second)) {
            std::cout << "Exception insert pair to dictionary. \n "
                      <<  "Input data do not satisfy the specification. \n";
            std::exit(1);
        }
    }

    CEqueue RPN;
    for (auto i: expressions){
        RPN.push(composite_expression(i.get_reverse_polish_notation()));
    }

    int M_buf = M;
    int M_buf_last = -1;
    while(!RPN.empty()){
        M_buf = queue_calculate(dictionary, RPN, M_buf);
        if (M_buf == M_buf_last) break;
        M_buf_last = M_buf;
    }

    for(auto i : dictionary) {
        DictionaryMap:: iterator it = buf_dictionary.find(i.first);
        if( it == buf_dictionary.end()) {
            if (i.second == -1)
                output_file << '?' << '\n';
            else
                output_file << i.second << '\n';
        }
    }

    return 0;
}