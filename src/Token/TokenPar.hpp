//
// Created by daftmat on 23/10/19.
//

#ifndef RPN_TOKENPAR_HPP
#define RPN_TOKENPAR_HPP

#include "TokenOpe.hpp"

class TokenPar : public TokenOpe {
public:
    /// Constructors
    explicit TokenPar(const std::string & str) : TokenOpe { *str.c_str() } {}
    explicit TokenPar(char op) : TokenOpe { op } {}

    TokenType type() const override { return PARENTHESIS; }
};


#endif //RPN_TOKENPAR_HPP
