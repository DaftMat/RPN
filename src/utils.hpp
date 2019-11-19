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

/**
 * Turns a string into a string list
 *  -> separates numbers and operators
 *  \helper_function used in stringToTokens
 * @param s string to be split into strings
 * @return the string list
 */
std::vector<std::string> split(const std::string & s);
std::vector<std::string> split_std(const std::string & s, char sep);

/**
 * Turns a string into a token list
 * @param s string to be split into tokens
 * @return the token list
 */
std::vector<std::shared_ptr<Token>> stringToTokens(const std::string &s);

/**
 * Returns the type
 * @param str string to be tested
 * @return 0 for a number, the priority of the operator if it's an operator (4 and 5 for parenthesis)
 */
int getType(const std::string & str);

/**
 * Tells if a character is an operator
 * @param c character to be tested
 * @return 0 if it's not an operator, else, returns the priority
 */
int isOperator(char c);

/**
 * Tells if a character is a digit
 * @param c character to be tested
 * @return true if it's a digit.
 */
bool isDigit(char c);

/**
 * Turns a string into a queue of Token to be parsed as RPN expression
 * @param s string to be parsed
 * @return RPN token queue
 */
std::queue<std::shared_ptr<Token>> rpnFromString(const std::string & s);

/**
 * Apply an operator token to 2 operands tokens
 * @param t1 1st operand token
 * @param t2 2nd operand token
 * @param op operator token
 * @return the resulting number token
 */
TokenNum applyOperator(const TokenNum &t1, const TokenNum &t2, const TokenOpe &op);

#endif //TP1_UTILS_HPP
