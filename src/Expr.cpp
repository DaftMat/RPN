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

std::map<std::string, double> Expr::m_vars;
std::map<std::string, std::function<double(std::vector<double>)>> Expr::m_func;

Expr::Expr(const char * expr) : m_expr { expr } {
    m_hasSemi = std::regex_match(m_expr, std::regex(".*;"));
}

void Expr::print() const {
    std::cout << m_expr << std::endl;
}

double Expr::eval() const {
    try {
        // get the RPN queue
        auto rpn = rpnFromString(m_expr);
        std::stack<TokenNum> values;
        // parse it
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

bool Expr::hasSemi() const {
    return m_hasSemi;
}

std::istream& operator>>(std::istream &is, Expr & expr) {
    std::getline(is, expr.m_expr);
    if (std::regex_match(expr.m_expr, std::regex("[( \t]*[) \t]*"))) ///check if there are only spaces (or only parenthesis)
        expr.m_expr = "0";
    expr.m_hasSemi = std::regex_match(expr.m_expr, std::regex(".*;"));
    expr.m_isVarDecl = std::regex_match(expr.m_expr, std::regex("[a-zA-Z]+[ \t]*=.*"));

    if (expr.m_isVarDecl) {
        auto temp = split_std(expr.m_expr, '=');
        expr.m_expr = temp[1];
        if (Expr::m_vars.count(temp[0]) == 0) {
            try {
                Expr::m_vars.insert(std::make_pair(temp[0], expr.eval()));
            } catch (NotAnExpression &e) {
                throw NotAnExpression(e);
            } catch (EmptyExpression &e) {
                throw EmptyExpression(e);
            }
        }
        else Expr::m_vars.at(temp[0]) = expr.eval();
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Expr & expr) {
    os << expr.m_expr;
    return os;
}