//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/function_signature.hpp"

using namespace std;
using namespace llvm;

namespace nl {

FunctionSignatureAST::FunctionSignatureAST(const string &name,
                                           vector<unique_ptr<VariableAST>> &args,
                                           Type *return_type) {
    m_name = name;
    m_args = move(args);
    m_return_type = return_type;
}

const string &FunctionSignatureAST::get_name() const {
    return m_name;
}

const vector<unique_ptr<VariableAST>> &FunctionSignatureAST::get_args() const {
    return m_args;
}

const Type *const &FunctionSignatureAST::get_return_type() const {
    return m_return_type;
}

Function *FunctionSignatureAST::make_IR(ValueMap &scope) const {
    vector<Type *> arg_types;
    for (const auto &arg : m_args) {
        arg_types.push_back(arg->get_type());
    }

    FunctionType *ft = FunctionType::get(m_return_type, arg_types, false);

    Function *f = Function::Create(ft, Function::ExternalLinkage, m_name, *mod);

    size_t i = 0;
    for (auto &arg : f->args()) {
        string name = m_args[i++]->get_name();
        arg.setName(name);
        scope[name] = &arg;
    }

    return f;
}

}
