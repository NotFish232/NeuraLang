//
// Created by piuslee on 2/18/23.
//

#ifndef NUMBEREXPRAST_HPP
#define NUMBEREXPRAST_HPP

#include "exprAST.hpp"

// abstract syntax tree for numeric values
class NumberExprAST : public ExprAST {
    double m_val;

public:
    // initializer list, assigns variable to class.  think getters & setters
    NumberExprAST(double val);
    llvm::Value *codegen() override;
};

#endif
