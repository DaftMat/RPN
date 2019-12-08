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
#include "Token/TokenFun.hpp"

std::map<std::string, double> Expr::m_vars;
std::map<std::string, std::function<double(std::deque<double>)>> Expr::m_func;
std::map<std::string, std::string> Expr::m_usrFunc;

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
        std::stack<std::shared_ptr<Token>> values;
        // parse it
        while (!rpn.empty()) {
            if (rpn.front()->type() == Token::NUMBER || rpn.front()->type() == Token::PARENTHESIS) {
                values.push(rpn.front());
            } else if (rpn.front()->type() == Token::FUNCTION) {
                std::deque<double> args;
                if (values.empty()) throw WrongArgument();
                while (values.top()->type() != Token::PARENTHESIS) {
                    if (values.empty()) throw WrongArgument();
                    args.push_front(dynamic_cast<TokenNum &>(*values.top()).value());
                    values.pop();
                }
                values.pop();//get rid of the parenthesis
                values.push(std::shared_ptr<Token>(new TokenNum(dynamic_cast<TokenFun &>(*rpn.front()).applyFunction(args))));
            } else {
                if (values.empty()) throw NotAnExpression("a number is missing");
                auto t1 = values.top();
                values.pop();
                if (values.empty()) throw NotAnExpression("a number is missing");
                auto t2 = values.top();
                values.pop();
                values.push(std::shared_ptr<Token>(applyOperator(dynamic_cast<TokenNum &>(*t1), dynamic_cast<TokenNum &>(*t2), dynamic_cast<TokenOpe &>(*rpn.front()))));
            }
            rpn.pop();
        }
        double ret = dynamic_cast<TokenNum &>(*values.top()).value();
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
                if (std::regex_match(expr.m_expr, std::regex("polynome(.*);"))) {
                    std::string f = expr.m_expr;
                    f.pop_back();
                    f.pop_back();
                    f.push_back(',');
                    Expr::m_usrFunc.insert(std::make_pair(temp[0], f));
                } else
                    Expr::m_vars.insert(std::make_pair(temp[0], expr.eval()));
            } catch (NotAnExpression &e) {
                throw NotAnExpression(e);
            } catch (EmptyExpression &e) {
                throw EmptyExpression(e);
            } catch (WrongArgument &e) {
                std::string f = expr.m_expr;
                f.pop_back();
                f.pop_back();
                f.push_back(',');
                Expr::m_usrFunc.insert(std::make_pair(temp[0], f));
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