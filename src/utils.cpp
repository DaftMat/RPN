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
        } else if ( c != ' ' && c != '\n' && c != '\t' && c != ','){
            std::string cha { c };
            throw NotAnExpression("unknown operator `"+cha+"`.");
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
        bool funcEntered = false;
        bool scdFuncEntered = false;
        bool firstPara = false;
        std::vector<std::shared_ptr<Token>> ret;
        std::string funcName;
        std::vector<double> funcArgs;
        std::string exprArg;
        for (auto &str : stringList) {
            int prio = getType(str);
            if (prio == 4) {
                if (!funcEntered) ret.push_back(std::shared_ptr<Token>(new TokenPar(str)));
                else if (!firstPara) exprArg.append(str);
                firstPara = false;
            } else if (prio == 5) {
                if (funcEntered) {
                    if (scdFuncEntered) {
                        exprArg.append(str);
                        scdFuncEntered = false;
                    } else {
                        if (!exprArg.empty()) funcArgs.push_back(Expr(exprArg.c_str()).eval());
                        double funcRet = Expr::m_func.at(funcName)(funcArgs);
                        ret.push_back(std::shared_ptr<Token>(new TokenNum(funcRet)));
                        exprArg.erase();
                        funcArgs.clear();
                    }
                } else ret.push_back(std::shared_ptr<Token>(new TokenPar(str)));
            } else if (prio == 7) {
                if (!funcEntered) throw NotAnExpression("Unknown operator " + str);
                if (scdFuncEntered) exprArg.append(str);
                else {
                    funcArgs.push_back(Expr(exprArg.c_str()).eval());
                    exprArg.erase();
                }
            } else if (prio > 0 && prio !=6) {
                if (funcEntered) exprArg.append(str);
                else ret.push_back(std::shared_ptr<Token>(new TokenOpe(str)));
            } else if (!prio){
                if (funcEntered) exprArg.append(str);
                else ret.push_back(std::shared_ptr<Token>(new TokenNum(str)));
            } else if (prio < 0) {
                if (Expr::m_vars.count(str))
                    ret.push_back(std::shared_ptr<Token>(new TokenNum(Expr::m_vars.at(str))));
                else if (Expr::m_func.count(str)) {
                    if (!funcEntered) {
                        funcName = str;
                        firstPara = true;
                    }
                    else {
                        exprArg.append(str);
                        scdFuncEntered = true;
                    }
                    funcEntered = true;
                }
                else throw NotAnExpression("name \"" + str + "\" doesn't exist");
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
    if (c == ',')
        return 7;
    if (isDigit(c))
        return 0;
    return -1;
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
        bool lastWasNumber = false;
        int numParenthesis = 0;
        for (auto &t : tokenList) {
            if (t->type() == Token::NUMBER) {
                if (lastWasNumber) throw NotAnExpression("two consecutive numbers were found.");
                ret.push(t);
                lastWasNumber = true;
            } else if (t->type() == Token::OPERATOR) {
                if (!lastWasNumber)
                    throw NotAnExpression("two consecutive operators were found, or the expression starts with one.");
                while (!op_stack.empty() && op_stack.top()->priority() >= t->priority()
                       && op_stack.top()->type() != Token::PARENTHESIS) {
                    ret.push(op_stack.top());
                    op_stack.pop();
                }
                op_stack.push(t);
                lastWasNumber = false;
            } else if (t->type() == Token::PARENTHESIS && t->priority() == 4) {// 4 for opening parenthesis
                op_stack.push(t);
                ++numParenthesis;
            } else if (t->type() == Token::PARENTHESIS && t->priority() == 5) {// 5 for closing parenthesis
                if (op_stack.empty()) throw NotAnExpression("missing opening parenthesis.");
                while (!op_stack.empty() && op_stack.top()->type() != Token::PARENTHESIS) {
                    ret.push(op_stack.top());
                    op_stack.pop();
                }
                if (op_stack.empty()) throw NotAnExpression("missing opening parenthesis.");
                op_stack.pop();
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

TokenNum applyOperator(const TokenNum &t1, const TokenNum &t2, const TokenOpe &op) {
    switch (op.value()) {
        case '+':
            return t1 + t2;
        case '-':
            return t2 - t1;
        case '*':
            return t1 * t2;
        case '/':
            return t2 / t1;
        case '^':
            return t2 ^ t1;
        default:
            throw NotAnExpression("unknown operator "+std::to_string(op.value())+".");
    }
}

void add_function(const std::string & name, int argc, const std::function<double(std::vector<double>)> & fun) {
    Expr::m_func.insert(std::make_pair(name, [fun, argc](const std::vector<double> & args) {
        if (args.size() != argc)
            throw NotAnExpression("Wrong argument number");
        return fun(args);
    }));
}

void init_base_functions() {
    add_function("sin", 1, [](const std::vector<double> & args){ return std::sin(args[0]); });
    add_function("cos", 1, [](const std::vector<double> & args){ return std::cos(args[0]); });
    add_function("tan", 1, [](const std::vector<double> & args){ return std::tan(args[0]); });
    add_function("sqrt", 1, [](const std::vector<double> & args){ return std::sqrt(args[0]); });
    add_function("log", 1, [](const std::vector<double> & args){ return std::log(args[0]); });
    add_function("exp", 1, [](const std::vector<double> & args){ return std::exp(args[0]); });
    add_function("pow", 2, [](const std::vector<double> & args){ return std::pow(args[0], args[1]); });
}
