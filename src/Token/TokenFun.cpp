//
// Created by daftmat on 08/12/19.
//

#include "TokenFun.hpp"

double TokenFun::applyFunction(const std::deque<double> &args) const {
    if (Expr::m_func.count(m_name)) {
        return Expr::m_func.at(m_name)(args);
    } else {
        Expr ret((Expr::m_usrFunc.at(m_name)+std::to_string(args[0])+")").c_str());
        return ret.eval();
    }
}