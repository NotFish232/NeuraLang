//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/CallExprAST.hpp"

llvm::Value *CallExprAST::codegen() {
    llvm::Function *CalleeF = mod->getFunction(Callee);

    if (!CalleeF) {
        Logger::error("Unknown function referenced");
        return nullptr;
    }

    if (CalleeF->arg_size() != Args.size()) {
        Logger::error("Incorrect # arguments passed");
        return nullptr;
    }

    std::vector<llvm::Value *> ArgsV;
    for (unsigned i = 0, e = Args.size(); i != e; i++) {
        ArgsV.push_back(Args[i]->codegen());

        if (!ArgsV.back()) {
            return nullptr;
        }
    }

    return builder.CreateCall(CalleeF, ArgsV, "calltmp");
}