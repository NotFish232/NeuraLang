//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/BinaryExprAST.hpp"

llvm::Value *BinaryExprAST::codegen() {
    llvm::Value *L = LHS->codegen();
    llvm::Value *R = RHS->codegen();

    if (!L || !R) return nullptr;

    switch (operation) {
        case '+':
            return builder.CreateFAdd(L, R, "addtmp");
        case '-':
            return builder.CreateFSub(L, R, "subtmp");
        case '*':
            return builder.CreateFMul(L, R, "multmp");
        case '<':
            L = builder.CreateFCmpULT(L, R, "cmptmp");
            return builder.CreateUIToFP(L, llvm::Type::getDoubleTy(ctx), "booltmp");
        default:
            return LogErrorV("Invalid binary operator");
    }
}