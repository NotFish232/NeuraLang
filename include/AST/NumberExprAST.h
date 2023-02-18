//
// Created by piuslee on 2/18/23.
//

#ifndef NUMBEREXPRAST_H
#define NUMBEREXPRAST_H

#include "ExprAST.h"

//abstract syntax tree for numeric values
class NumberExprAST: public ExprAST {
    double Val;

public:
    //initializer list, assigns variable to class.  think getters & setters
    NumberExprAST(double Val): Val(Val) {}
    llvm::Value *codegen() override;
};

#endif
