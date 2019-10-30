//
// Created by daftmat on 15/10/19.
//

#ifndef TP1_UTILS_HPP
#define TP1_UTILS_HPP

#include <vector>
#include <queue>
#include <string>
#include <memory>

#include "Token/Token.hpp"

class TokenNum;
class TokenOpe;

std::vector<std::string> split(const std::string & s);
std::vector<std::shared_ptr<Token>> stringToTokens(const std::string &s);
int getType(const std::string & str);
int isOperator(char c);
bool isDigit(char c);
std::queue<std::shared_ptr<Token>> rpnFromString(const std::string & s);
TokenNum applyOperator(const TokenNum &t1, const TokenNum &t2, const TokenOpe &op);

struct EmptyDel {
    void operator()(std::istream *) {}
};

#endif //TP1_UTILS_HPP
