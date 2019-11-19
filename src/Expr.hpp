//
// Created by daftmat on 15/10/19.
//

#ifndef TP1_EXPR_HPP
#define TP1_EXPR_HPP

#include <map>

/// Expression class
class Expr {

public:
    static std::map<std::string, double> m_vars;

    /// Constructors
    Expr() : m_expr { "0" }, m_hasSemi { false }, m_isVarDecl { false } {}
    explicit Expr(const char * expr);

    /**
     * Evaluates expression
     * @return the result of the expression
     */
    double eval() const;

    /**
     * Prints the intern representation of the expression
     * (Using << operator to stdout in the application)
     */
    void print() const;

    bool hasSemi() const;

    /// stream operators
    friend std::istream& operator>>(std::istream &is, Expr & expr);
    friend std::ostream& operator<<(std::ostream &os, const Expr & expr);

private:
    std::string m_expr;
    bool m_hasSemi;
    bool m_isVarDecl;
};

#endif //TP1_EXPR_HPP
