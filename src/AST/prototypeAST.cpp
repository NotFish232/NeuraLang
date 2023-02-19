//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/prototypeAST.hpp"

using namespace std;
using namespace llvm;

PrototypeAST::PrototypeAST(const string &name, vector<string> args)
    : m_name(name), m_args(std::move(args)) {}

Function *PrototypeAST::codegen() {
    vector<Type *> Doubles(m_args.size(), Type::getDoubleTy(ctx));
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(ctx), Doubles, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, m_name, mod.get());

    size_t i = 0;
    for (auto &arg : F->args()) {
        arg.setName(m_args[i++]);
    }

    return F;
}

const string &PrototypeAST::getName() const {
    return m_name;
}