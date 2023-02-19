//
// Created by piuslee on 2/18/23.
//

#ifndef FUNCTIONAST_HPP
#define FUNCTIONAST_HPP

#include "exprAST.hpp"
#include "prototypeAST.hpp"

// function syntax tree
// this represents the function itself.
class FunctionAST {
    std::unique_ptr<PrototypeAST> m_proto;
    std::unique_ptr<ExprAST> m_body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> m_proto, std::unique_ptr<ExprAST> m_body);
    llvm::Function *codegen();
};

#endif
