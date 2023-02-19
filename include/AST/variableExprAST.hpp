//
// Created by piuslee on 2/18/23.
//

#ifndef VARIABLEEXPRAST_HPP
#define VARIABLEEXPRAST_HPP

#include "exprAST.hpp"

// syntax tree for variables
class VariableExprAST : public ExprAST {
    std::string m_name;

public:
    VariableExprAST(const std::string &Name);
    llvm::Value *codegen() override;
};

#endif