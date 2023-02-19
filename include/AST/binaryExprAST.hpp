//
// Created by piuslee on 2/18/23.
//

#ifndef BINARYEXPRAST_HPP
#define BINARYEXPRAST_HPP

#include "exprAST.hpp"

// syntax tree for binary
class BinaryExprAST : public ExprAST {
    char m_operator;
    std::unique_ptr<ExprAST> m_left, m_right;

public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> left, std::unique_ptr<ExprAST> right);
    llvm::Value *codegen() override;
};

#endif
