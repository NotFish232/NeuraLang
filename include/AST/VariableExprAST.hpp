//
// Created by piuslee on 2/18/23.
//

#ifndef VARIABLEEXPRAST_HPP
#define VARIABLEEXPRAST_HPP

#include "ExprAST.hpp"

//syntax tree for variables
class VariableExprAST : public ExprAST {
    std::string Name;

public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
    llvm::Value *codegen() override;
};

#endif