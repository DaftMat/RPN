//
// Created by daftmat on 15/10/19.
//

#include <stack>
#include <cmath>
#include <iostream>
#include <sstream>
#include <ctype.h>

#include "utils.hpp"
#include "NotAnExpression.hpp"
#include "Token/TokenNum.hpp"
#include "Token/TokenOpe.hpp"
#include "Token/TokenPar.hpp"
#include "Expr.hpp"
#include "Token/TokenFun.hpp"

std::vector<std::string> split(const std::string & s) {
    std::vector<std::string> ret;
    std::string current;
    for(char c : s) {
        if (isDigit(c) || isalpha(c)){
            current.push_back(c);
        } else if (isOperator(c) > 0) {
            if (!current.empty()) {
                ret.push_back(current);
                current.erase();
            }
            current.push_back(c);
            ret.push_back(current);
            current.erase();
        } else if ( c != ' ' && c != '\n' && c != '\t' && c != ',' ){
            std::string cha { c };
            throw NotAnExpression("unknown operator `"+cha+"`.");
        } else if ( c == ',' ) {
            if (!current.empty()) {
                ret.push_back(current);
                current.erase();
            }
        }
    }
    if (!current.empty()) {
        ret.push_back(current);
        current.erase();
    }
    return ret;
}

std::vector<std::string> split_std(const std::string &s, char sep) {
    std::vector<std::string> tokens;
    std::string token;
    for (auto c : s)
    {
        if (c == sep) {
            if (!token.empty())
                tokens.push_back(token);
            token.erase();
        } else if (c != ' ' && c != '\t') {
            token.push_back(c);
        }
    }
    if (!token.empty())
        tokens.push_back(token);
    return tokens;
}

std::vector<std::shared_ptr<Token>> stringToTokens(const std::string &s) {
    try {
        auto stringList = split(s);
        std::vector<std::shared_ptr<Token>> ret;
        for (auto &str : stringList) {
            int prio = getType(str);
            if (prio > 3 && prio != 6) { //dont add it if it's `;`
                ret.push_back(std::shared_ptr<Token>(new TokenPar(str)));
            } else if (prio > 0 && prio !=6) {
                ret.push_back(std::shared_ptr<Token>(new TokenOpe(str)));
            } else if (!prio){
                ret.push_back(std::shared_ptr<Token>(new TokenNum(str)));
            } else if (prio == -1) {
                if (Expr::m_vars.count(str))    ret.push_back(std::shared_ptr<Token>(new TokenNum(Expr::m_vars.at(str))));
                else if (Expr::m_func.count(str) || Expr::m_usrFunc.count(str)){
                    ret.push_back(std::shared_ptr<Token>(new TokenFun(str)));
                }
                else throw NotAnExpression("undefined function or variable " + str);
            }
        }
        return ret;
    } catch (NotAnExpression& exc) {
        throw NotAnExpression(exc);
    }
}

int getType(const std::string & str) {
    return isOperator(str[0]);
}

int isOperator(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    if (c == '(')
        return 4;
    if (c == ')')
        return 5;
    if (c == ';')
        return 6;
    if (isDigit(c))
        return 0;
    return -1;///if variable name
}

bool isDigit(char c) {
    return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
            c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.');
}

std::queue<std::shared_ptr<Token>> rpnFromString(const std::string & s) {
    try {
        auto tokenList = stringToTokens(s);
        std::stack<std::shared_ptr<Token>> op_stack;
        std::queue<std::shared_ptr<Token>> ret;
        int numParenthesis = 0;
        for (auto &t : tokenList) {
            if (t->type() == Token::NUMBER) {
                ret.push(t);
            } else if (t->type() == Token::FUNCTION) {
                ret.push(std::shared_ptr<Token>(new TokenPar(';'))); // to get the number of arguments
                op_stack.push(t);
            } else if (t->type() == Token::OPERATOR) {
                while (!op_stack.empty() && op_stack.top()->priority() >= t->priority()
                       && op_stack.top()->type() != Token::PARENTHESIS) {
                    ret.push(op_stack.top());
                    op_stack.pop();
                }
                op_stack.push(t);
            } else if (t->type() == Token::PARENTHESIS && t->priority() == 4) {// 4 for opening parenthesis
                op_stack.push(t);
                ++numParenthesis;
            } else if (t->type() == Token::PARENTHESIS && t->priority() == 5) {// 5 for closing parenthesis
                if (op_stack.empty()) throw NotAnExpression("missing opening parenthesis.");
                while (op_stack.top()->type() != Token::PARENTHESIS) {
                    if (op_stack.empty()) throw NotAnExpression("missing opening parenthesis.");
                    ret.push(op_stack.top());
                    op_stack.pop();
                }
                op_stack.pop();//pop the parenthesis
                if (op_stack.top()->type() == Token::FUNCTION) {
                    ret.push(op_stack.top());
                    op_stack.pop();
                }
                --numParenthesis;
            }
        }
        if (numParenthesis) throw NotAnExpression("missing closing parenthesis.");
        while (!op_stack.empty()) {
            ret.push(op_stack.top());
            op_stack.pop();
        }
        return ret;
    } catch (NotAnExpression& exc) {
        throw NotAnExpression(exc);
    }
}

TokenNum * applyOperator(const TokenNum &t1, const TokenNum &t2, const TokenOpe &op) {
    auto *ret = new TokenNum(0);
    switch (op.value()) {
        case '+':
            *ret = t1 + t2;
            break;
        case '-':
            *ret = t2 - t1;
            break;
        case '*':
            *ret = t1 * t2;
            break;
        case '/':
            *ret = t2 / t1;
            break;
        case '^':
            *ret = t2 ^ t1;
            break;
        default:
            throw NotAnExpression("unknown operator "+std::to_string(op.value())+".");
    }
    return ret;
}

void add_function(const std::string & name, int argc, const std::function<double(std::deque<double>)> & fun) {
    Expr::m_func.insert(std::make_pair(name, [fun, argc](const std::deque<double> & args) {
        if (args.size() != argc)
            throw WrongArgument();
        return fun(args);
    }));
}

void init_base_functions() {
    add_function("sin", 1, [](const std::deque<double> & args){ return std::sin(args[0]); });
    add_function("cos", 1, [](const std::deque<double> & args){ return std::cos(args[0]); });
    add_function("tan", 1, [](const std::deque<double> & args){ return std::tan(args[0]); });
    add_function("sqrt", 1, [](const std::deque<double> & args){ return std::sqrt(args[0]); });
    add_function("log", 1, [](const std::deque<double> & args){ return std::log(args[0]); });
    add_function("exp", 1, [](const std::deque<double> & args){ return std::exp(args[0]); });
    add_function("pow", 2, [](const std::deque<double> & args){ return std::pow(args[0], args[1]); });
    add_function("hypot", 2, [](const std::deque<double> &args){ return std::sqrt(std::pow(args[0], 2) + std::pow(args[1], 2)); });
    add_function("lerp", 3, [](const std::deque<double> &args){ return args[0] + (args[1] - args[0]) * args[2]; });

    Expr::m_func.insert(std::make_pair("polynome", [](const std::deque<double> & args) {
        double d = args[0];
        double x = args[args.size() - 1];
        double res = 0;
        for (int i = 0 ; i <= d ; ++i) res += args[i+1] * std::pow(x, i);
        return res;
    }));
}