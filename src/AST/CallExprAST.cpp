//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/CallExprAST.hpp"

llvm::Value *CallExprAST::codegen() {
    llvm::Function *CalleeF = mod -> getFunction(Callee);

    if (!CalleeF) {
        return LogErrorV("Unknown function referenced");
    }

    if (CalleeF -> arg_size() != Args.size()) {
        return LogErrorV("Incorrect # arguments passed");
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