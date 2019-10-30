//
// Created by daftmat on 15/10/19.
//

#include <iostream>
#include <stack>
#include <regex>

#include "Token/Token.hpp"
#include "Token/TokenNum.hpp"
#include "Token/TokenOpe.hpp"
#include "utils.hpp"

#include "Expr.hpp"
#include "NotAnExpression.hpp"

void Expr::print() const {
    std::cout << m_expr << std::endl;
}

double Expr::eval() const {
    if (m_expr == "0") throw EmptyExpression();
    try {
        auto rpn = rpnFromString(m_expr);
        std::stack<TokenNum> values;
        while (!rpn.empty()) {
            if (rpn.front()->type() == Token::NUMBER) {
                values.push(dynamic_cast<TokenNum &>(*rpn.front()));
            } else {
                auto t1 = values.top();
                values.pop();
                TokenNum t2(0);
                if (values.empty()) throw NotAnExpression("a number is missing");
                else {
                    t2 = values.top();
                    values.pop();
                }
                values.push(applyOperator(t1, t2, dynamic_cast<TokenOpe &>(*rpn.front())));
            }
            rpn.pop();
        }
        double ret = values.top().value();
        values.pop();
        return ret;
    } catch (NotAnExpression& err) {
        throw NotAnExpression(err);
    }
}

std::istream& operator>>(std::istream &is, Expr & expr) {
    std::getline(is, expr.m_expr);
    if (std::regex_match(expr.m_expr, std::regex("[( \t]*[) \t]*"))) ///check if there are only spaces (or only parenthesis)
        expr.m_expr = "0";
    return is;
}

std::ostream& operator<<(std::ostream &os, const Expr & expr) {
    os << expr.m_expr;
    return os;
}