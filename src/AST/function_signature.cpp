//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/function_signature.hpp"

using namespace std;
using namespace llvm;

namespace nl {

FunctionSignatureAST::FunctionSignatureAST(const string &name, const vector<unique_ptr<VariableAST>> &args, const string &returnTypeStr) {
    m_name = name;
    /*m_args.reserve(args.size());
    for (const auto &arg: args) {
        m_args.push_back(move(arg));
    }*/
    m_returnType = get_type_from_str(returnTypeStr);
}

const string &FunctionSignatureAST::get_name() const {
    return m_name;
}

const vector<unique_ptr<VariableAST>> &FunctionSignatureAST::get_args() const {
    return m_args;
}

const Type *const &FunctionSignatureAST::get_return_type() const {
    return m_returnType;
}

Function *FunctionSignatureAST::make_IR() {
    /*vector<Type *> Doubles(m_args.size(), Type::getDoubleTy(*ctx));
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(*ctx), Doubles, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, m_name, mod.get());

    size_t i = 0;
    for (auto &arg : F->args()) {
        arg.setName(m_args[i++]);
    }

    return F;*/
    return nullptr;
}

}
