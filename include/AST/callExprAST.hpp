//
// Created by piuslee on 2/18/23.
//

#ifndef CALLEXPRAST_HPP
#define CALLEXPRAST_HPP

#include "exprAST.hpp"

// function calls syntax tree
class CallExprAST : public ExprAST {
    std::string m_funcName;
    std::vector<std::unique_ptr<ExprAST>> m_args;

public:
    CallExprAST(const std::string &funcName, std::vector<std::unique_ptr<ExprAST>> args);
    llvm::Value *codegen() override;
};

#endif
