#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>

#include "composite_expression.h"
#include "expression_calculator.h"

inline void die(const std::string &msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) die("Usage: ./cppfile InputFile OutputFile.");

    std::ifstream input_file(argv[1]);
    if (!input_file.good()) die("Failed to open input file.");

    std::ofstream output_file(argv[2]);
    if (!output_file.good()) die("Failed to open output file.");

    int N;
    int M;
    input_file >> N >> M;

    ExpressionCalculator calculator;

    int value;
    std::string key;
    for (int i = 0; i < N; i++) {
        input_file >> key >> value;
        bool ok = calculator.add_simple_expression(key, value);
        if (!ok)
            die("Failed to insert pair to dictionary: "
                "input data does not satisfy the specification.");
    }

    std::string exp;
    std::getline(input_file, exp); // добиваю последнюю строку из предыдущего цикла
    while (!input_file.eof() && M > 0) {
        std::getline(input_file, exp);
        exp.erase(exp.find_last_not_of(" \n\r\t") + 1);
        bool ok = calculator.add_composite_expression(exp);
        if (!ok)
            die("Failed to insert pair to dictionary: "
                "input data does not satisfy the specification.");
        M--;
    }

    auto result = calculator.solve();
    for (auto r : result) {
        if (r == VALUE_UNKNOWN) output_file << '?' << std::endl;
        else output_file << r << std::endl;
    }

    return 0;
}