//
// Created by daftmat on 23/10/19.
//

#ifndef RPN_TOKENPAR_HPP
#define RPN_TOKENPAR_HPP

#include "TokenOpe.hpp"

class TokenPar : public TokenOpe {
public:
    explicit TokenPar(const std::string & str) : TokenOpe { *str.c_str() } {}
    explicit TokenPar(char op) : TokenOpe { op } {}

    TokenPar(const TokenPar & token) = default;
    TokenPar(TokenPar && token) noexcept = default;

    TokenType type() const override { return PARENTHESIS; }
};


#endif //RPN_TOKENPAR_HPP
