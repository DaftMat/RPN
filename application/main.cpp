//
// Created by daftmat on 30/10/19.
//

#include <iostream>

#include <Expr.hpp>
#include <utils.hpp>

#include <NotAnExpression.hpp>
#include <fstream>
#include <memory>
#include "Program.hpp"

int main(int argc, char **argv) {
    std::shared_ptr<Program> prog;
    std::cout << "> Welcome to the RPN application.";
    if (argc == 1) {
        std::cout << " Type expressions (CTRL-D to end)." << std::endl;
        prog.reset(new Program);
    } else {
        std::cout << " Parsing the file..." << std::endl;
        prog.reset(new Program(argv[1]));
    }

    ///Parsing the file (that may be stdin)
    prog->exec();
    return 0;
}