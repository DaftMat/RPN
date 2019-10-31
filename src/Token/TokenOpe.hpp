//
// Created by daftmat on 23/10/19.
//

#ifndef RPN_TOKENOPE_HPP
#define RPN_TOKENOPE_HPP

#include "../utils.hpp"
#include "Token.hpp"

class TokenOpe : public Token {
public:
    /// Constructors
    explicit TokenOpe(const std::string & str) : m_op { *str.c_str() }, m_priority { getType(str) } {}
    explicit TokenOpe(char op) : m_op { op }, m_priority { isOperator(op) } {}

    /// Copy & Move Constructors
    TokenOpe(const TokenOpe & token) : m_op { token.m_op }, m_priority { token.m_priority } {}
    TokenOpe(TokenOpe && token) noexcept : m_op { token.m_op }, m_priority { token.m_priority } {}

    /// Copy & Move assignment operator overloads
    TokenOpe & operator=(const TokenOpe & token) { m_op = token.m_op; return *this; }
    TokenOpe & operator=(TokenOpe && token) noexcept { m_op = token.m_op; return *this; }

    /// type override
    TokenType type() const override { return OPERATOR; }

    /// Return the character version of the operator
    char value() const { return m_op; }

    /// priority override
    int priority() const override { return m_priority; }

private:
    char m_op;
    int m_priority;
};


#endif //RPN_TOKENOPE_HPP
