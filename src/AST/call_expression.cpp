//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/call_expression.hpp"

using namespace std;
using namespace llvm;

namespace nl {

CallExpressionAST::CallExpressionAST(const string &func_name, const vector<NodeAST> &args) {
    m_func_name = func_name;
    m_args = args;
}

CallExpressionAST::~CallExpressionAST() {
}

const string &CallExpressionAST::get_func_name() const {
    return m_func_name;
}

const vector<NodeAST> &CallExpressionAST::get_args() const {
    return m_args;
}

Value *CallExpressionAST::make_IR(ValueMap &scope) const {
    Function *func = mod->getFunction(m_func_name);

    if (!func) {
        return nullptr;
    }

    if (func->arg_size() != m_args.size()) {
        return nullptr;
    }

    vector<Value *> args;
    for (auto &arg : m_args) {
        args.push_back(arg.make_IR(scope));
        if (!args.back()) {
            return nullptr;
        }
    }

    return builder->CreateCall(func, args);
}

}