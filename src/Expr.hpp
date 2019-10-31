//
// Created by daftmat on 15/10/19.
//

#ifndef TP1_EXPR_HPP
#define TP1_EXPR_HPP

/// Expression class
class Expr {

public:
    /// Constructors
    Expr() : m_expr { "0" } {}
    explicit Expr(const char * expr) : m_expr { expr } {}

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

    /// stream operators
    friend std::istream& operator>>(std::istream &is, Expr & expr);
    friend std::ostream& operator<<(std::ostream &os, const Expr & expr);

private:
    std::string m_expr;
};

#endif //TP1_EXPR_HPP
