//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/PrototypeAST.hpp"

llvm::Function *PrototypeAST::codegen(){
    std::vector<llvm::Type *> Doubles(Args.size(), llvm::Type::getDoubleTy(ctx));
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getDoubleTy(ctx), Doubles, false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, mod.get());

    unsigned i = 0;
    for(auto &Arg : F->args()) {
        Arg.setName(Args[i++]);
    }

    return F;
}