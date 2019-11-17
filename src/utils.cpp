//
// Created by daftmat on 15/10/19.
//

#include <stack>
#include <cmath>
#include <iostream>

#include "utils.hpp"
#include "NotAnExpression.hpp"
#include "Token/TokenNum.hpp"
#include "Token/TokenOpe.hpp"
#include "Token/TokenPar.hpp"

std::vector<std::string> split(const std::string & s) {
    std::vector<std::string> ret;
    std::string current;
    for(auto c : s) {
        if (isDigit(c)){
            current.push_back(c);
        } else if (isOperator(c)) {
            if (!current.empty()) {
                ret.push_back(current);
                current.erase();
            }
            current.push_back(c);
            ret.push_back(current);
            current.erase();
        } else if (c != ' ' && c != '\t' && c != ';'){
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

std::vector<std::shared_ptr<Token>> stringToTokens(const std::string &s) {
    try {
        auto stringList = split(s);
        std::vector<std::shared_ptr<Token>> ret;
        for (auto &str : stringList) {
            int prio = getType(str);
            if (prio > 3 && prio != 6) { //dont add it if it's `;`
                ret.push_back(std::shared_ptr<Token>(new TokenPar(str)));
            } else if (prio) {
                ret.push_back(std::shared_ptr<Token>(new TokenOpe(str)));
            } else {
                ret.push_back(std::shared_ptr<Token>(new TokenNum(str)));
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
    return 0;
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