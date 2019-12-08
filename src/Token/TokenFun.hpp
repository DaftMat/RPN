//
// Created by daftmat on 21/11/19.
//

#ifndef RPN_TOKENFUN_HPP
#define RPN_TOKENFUN_HPP

#include "../Expr.hpp"
#include "Token.hpp"

class TokenFun : public Token {
public:
    explicit TokenFun(const std::string &name) : m_name { name } {}

    TokenType type() const override { return FUNCTION; }

    int priority() const override { return 7; }

    const std::string& name() const { return m_name; }

    double applyFunction(const std::deque<double> &args) const;

private:
    std::string m_name;
};

#endif //RPN_TOKENFUN_HPP
