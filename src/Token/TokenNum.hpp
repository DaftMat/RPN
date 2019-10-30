//
// Created by daftmat on 23/10/19.
//

#ifndef RPN_TOKENNUM_HPP
#define RPN_TOKENNUM_HPP

#include "Token.hpp"
#include <cmath>

class TokenNum : public Token {
public:
    explicit TokenNum(const std::string & str) : m_value { std::stod(str) } {}
    explicit TokenNum(double value) : m_value { value } {}

    TokenNum(const TokenNum & token) : m_value { token.m_value } {}
    TokenNum(TokenNum && token) noexcept : m_value { token.m_value } {}

    TokenNum & operator=(const TokenNum &token) { m_value = token.m_value; return *this; }

    const TokenNum operator+(const TokenNum &token) const { return TokenNum(m_value + token.m_value); }
    const TokenNum operator-(const TokenNum &token) const { return TokenNum(m_value - token.m_value); }
    const TokenNum operator*(const TokenNum &token) const { return TokenNum(m_value * token.m_value); }
    const TokenNum operator/(const TokenNum &token) const { return TokenNum(m_value / token.m_value); }
    const TokenNum operator^(const TokenNum &token) const { return TokenNum(std::pow(m_value, token.m_value)); }

    TokenType type() const override { return Token::NUMBER; }

    double value() const { return m_value; }

private:
    double m_value;
};


#endif //RPN_TOKENNUM_HPP
