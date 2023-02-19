//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/FunctionAST.hpp"

llvm::Function *FunctionAST::codegen() {
    llvm::Function *function = mod->getFunction(Proto->getName());

    if (!function)
        function = Proto->codegen();
    if (!function)
        return nullptr;

    llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx, "entry", function);
    builder.SetInsertPoint(block);
    values.clear();

    for (auto &Arg : function->args()) {
        values[Arg.getName().data()] = &Arg;
    }

    if (llvm::Value *returnedValue = Body->codegen()) {
        builder.CreateRet(returnedValue);
        verifyFunction(*function);

        return function;
    }

    function->eraseFromParent();
    return nullptr;
}