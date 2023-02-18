//
// Created by piuslee on 2/18/23.
//

#ifndef FUNCTIONAST_H
#define FUNCTIONAST_H

#include "ExprAST.h"
#include "PrototypeAST.h"

//function syntax tree
//this represents the function itself.
class FunctionAST {
    std::unique_ptr < PrototypeAST > Proto;
    std::unique_ptr < ExprAST > Body;

public:
    FunctionAST(std::unique_ptr < PrototypeAST > Proto, std::unique_ptr < ExprAST > Body): Proto(std::move(Proto)), Body(std::move(Body)) {}
    llvm::Function *codegen();
};

#endif
