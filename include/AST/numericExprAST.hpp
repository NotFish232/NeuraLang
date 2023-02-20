//
// Created by piuslee on 2/18/23.
//

#ifndef NUMERICEXPRAST_HPP
#define NUMERICEXPRAST_HPP

#include "exprAST.hpp"

// abstract syntax tree for numeric values
class NumericExprAST : public ExprAST {
    double m_val;

public:
    // initializer list, assigns variable to class.  think getters & setters
    NumericExprAST(double val);
    llvm::Value *codegen() override;
};

#endif
