//
// Created by daftmat on 23/10/19.
//

#ifndef RPN_TOKEN_HPP
#define RPN_TOKEN_HPP


#include <string>

/**
 * Token base class
 */
class Token {
public:
    enum TokenType {
        NUMBER,
        OPERATOR,
        PARENTHESIS
    };
    virtual ~Token() = default;

    ///Pure virtual type returning function
    virtual TokenType type() const = 0;

    ///Virtual function for priority, 0 by default
    virtual int priority() const { return 0; }
};


#endif //RPN_TOKEN_HPP
