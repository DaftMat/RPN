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

    /// Getting the input from the args:
    /// if no args, stdin, if there's an arg, it will be a file to be parsed.
    std::shared_ptr<std::istream> input;
    bool inputIsStdin = false;
    std::cout << "> Welcome to the RPN application.";
    if (argc == 1) {
        input.reset(&std::cin, EmptyDel());
        inputIsStdin = true;
        std::cout << " Type expressions (CTRL-D to end)." << std::endl;
    } else {
        input.reset(new std::ifstream(argv[1]));
        if (!(input)) {
            std::cerr << "> Error while opening file." << std::endl;
            return -1;
        }
        std::cout << " Parsing the file..." << std::endl;
    }

    ///Parsing the file (that may be stdin)
    Expr expr;
    if (inputIsStdin)   std::cout << "> ";
    while (*input >> expr) {
        try {
            double res = expr.eval();
            std::cout << "> " << expr << " = " << res << std::endl;
        } catch (NotAnExpression& e) {
            std::cerr << "> " << e.error() << std::endl;
        } catch (EmptyExpression& e) {
            std::cerr << "> " << e.error() << std::endl;
        }
        if (inputIsStdin)   std::cout << "> ";
    }
    if (!inputIsStdin)  std::cout << "> ";
    std::cout << "RPN application ended." << std::endl;
    return 0;
}