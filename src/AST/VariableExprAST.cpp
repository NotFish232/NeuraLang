//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/VariableExprAST.hpp"

llvm::Value *VariableExprAST::codegen() {
    llvm::Value *V = values[Name];

    if (!V)
        Logger::error("unknown var name");

    return V;
}