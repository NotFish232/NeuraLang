#ifndef IFEXPRAST_HPP
#define IFEXPRAST_HPP

#include "exprAST.hpp"

class IfExprAST : public ExprAST {
    std::unique_ptr<ExprAST> m_condition, m_then, m_else;

public:
    IfExprAST(std::unique_ptr<ExprAST> _condition, std::unique_ptr<ExprAST> _then, std::unique_ptr<ExprAST> _else);
    llvm::Value *codegen() override;
};

#endif
