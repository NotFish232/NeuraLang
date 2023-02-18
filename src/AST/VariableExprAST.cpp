//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/VariableExprAST.hpp"

llvm::Value *VariableExprAST::codegen() {
    llvm::Value *V = values[Name];

    if(!V) LogErrorV("unknown var name");

    return V;
}