//
// Created by daftmat on 30/10/19.
//

#ifndef RPN_NOTANEXPRESSION_HPP
#define RPN_NOTANEXPRESSION_HPP

#include <string>

/// Exceptions classes
/// Exception to be thrown when the parsed expression is invalid
class NotAnExpression {
public:
    explicit NotAnExpression(const std::string &msg) : m_msg { msg } {}

    NotAnExpression(const NotAnExpression& exc) : m_msg { exc.m_msg } {}
    NotAnExpression(NotAnExpression&& exc) : m_msg { exc.m_msg } {}

    std::string error() {
        return "Expression error : " + m_msg;
    }

private:
    std::string m_msg;
};

/// Exception to be thrown when the parsed expression is empty.
/// \note : a valid number of empty parenthesis will throw this exception (such as "((()))")
class EmptyExpression {
public:
    EmptyExpression() = default;

    EmptyExpression(const EmptyExpression& exc) {}
    EmptyExpression(EmptyExpression&& exc) {}

    std::string error() {
        return "Empty expression.";
    }
};

class WrongArgument {
public:
    WrongArgument() = default;

    WrongArgument(const WrongArgument &exc) {}
    WrongArgument(WrongArgument &&exc ) {}

    std::string error() {
        return "Wrong amount of arguments.";
    }
};

#endif //RPN_NOTANEXPRESSION_HPP
