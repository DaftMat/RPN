//
// Created by daftmat on 30/10/19.
//

#ifndef RPN_NOTANEXPRESSION_HPP
#define RPN_NOTANEXPRESSION_HPP


#include <string>

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

class EmptyExpression {
public:
    EmptyExpression() = default;

    EmptyExpression(const EmptyExpression& exc) {}
    EmptyExpression(EmptyExpression&& exc) {}

    std::string error() {
        return "Empty expression.";
    }
};


#endif //RPN_NOTANEXPRESSION_HPP
