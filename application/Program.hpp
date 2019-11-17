//
// Created by daftmat on 31/10/19.
//

#ifndef RPN_PROGRAM_HPP
#define RPN_PROGRAM_HPP

#include <iostream>
#include <fstream>
#include <memory>

class Program {
public:
    Program();
    explicit Program(char *path);

    /// forbid copy
    Program(const Program &) = delete;
    Program(Program &&) = delete;
    Program & operator=(const Program &) = delete;
    Program & operator=(Program &&) = delete;

    void exec();

private:
    std::shared_ptr<std::istream> m_input;
    bool m_inputIsStdin;
};

/// Helper class to have an empty delete function (to store std::cin into smart pointers)
struct EmptyDel {
    void operator()(std::istream *) {}
};

#endif //RPN_PROGRAM_HPP
