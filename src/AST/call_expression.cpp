//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/call_expression.hpp"

using namespace std;
using namespace llvm;

namespace nl {

CallExpressionAST::CallExpressionAST(const string &funcName, const vector<unique_ptr<NodeAST>> &args) {
        m_funcName = funcName;
       // m_args = args;
    }

CallExpressionAST::~CallExpressionAST() {

}

const string &CallExpressionAST::get_func_name() const {
    return m_funcName;
}

const vector<unique_ptr<NodeAST>> &CallExpressionAST::get_args() const {
    return m_args;
}

Value *CallExpressionAST::make_IR() {
    Function *func = mod->getFunction(m_funcName);

    if (!func) {
        return nullptr;
    }

    if (func->arg_size() != m_args.size()) {
        return nullptr;
    }

    vector<Value *> args;
    for (const auto &arg: m_args) {
        args.push_back(arg->make_IR());
        if (!args.back()) {
            return nullptr;
        }
    }

    return builder->CreateCall(func, args);
}

}