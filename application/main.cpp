//
// Created by daftmat on 30/10/19.
//

#include <iostream>

#include <Expr.hpp>
#include <utils.hpp>

#include <NotAnExpression.hpp>
#include <fstream>
#include <memory>

int main(int argc, char **argv) {

    std::shared_ptr<std::istream> input;
    if (argc == 1) {
        input.reset(&std::cin, EmptyDel());
        std::cout << "Welcome to the RPN application. Type expresions (CTRL-D to end)." << std::endl;
    }
    else {
        input.reset(new std::ifstream(argv[1]));
        if (!(input)) {
            std::cerr << "Error while opening file." << std::endl;
            return -1;
        }
    }

    Expr expr;
    while (*input >> expr) {
        try {
            double res = expr.eval();
            std::cout << expr << " = " << res << std::endl;
        } catch (NotAnExpression& e) {
            std::cerr << e.error() << std::endl;
        } catch (EmptyExpression& e) {
            std::cerr << e.error() << std::endl;
        }
    }
    return 0;
}