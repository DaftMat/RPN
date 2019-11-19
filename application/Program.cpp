//
// Created by daftmat on 31/10/19.
//

#include <NotAnExpression.hpp>
#include <Expr.hpp>
#include "Program.hpp"

Program::Program() : m_inputIsStdin { true } {
    m_input.reset(&std::cin, EmptyDel());
}

Program::Program(char *path) : m_inputIsStdin { false } {
    m_input.reset(new std::ifstream(path));///treated as an empty file if it doesnt exist
}

void Program::exec() {
    Expr expr;
    if (m_inputIsStdin)   std::cout << "> ";
    while (*m_input) {
        try {
            *m_input >> expr;
            if (!expr.hasSemi()) {
                double res = expr.eval();
                std::cout << "> " << expr << " = " << res << std::endl;
            }
        } catch (NotAnExpression& e) {
            std::cerr << "> " << e.error() << std::endl;
        } catch (EmptyExpression& e) {
            std::cerr << "> " << e.error() << std::endl;
        }
        if (m_inputIsStdin)   std::cout << "> ";
    }
    if (!m_inputIsStdin)  std::cout << "> ";
    std::cout << "RPN application ended." << std::endl;
}