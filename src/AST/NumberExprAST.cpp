//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/NumberExprAST.hpp"

llvm::Value *NumberExprAST::codegen() {
    return llvm::ConstantFP::get(ctx, llvm::APFloat(Val));
}