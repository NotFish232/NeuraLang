#include "../../../include/AST/functions/call_expression.hpp"

using namespace std;
using namespace llvm;

namespace nl {

CallExpressionAST::CallExpressionAST(const string &func_name, vector<unique_ptr<NodeAST>> &args) {
    m_func_name = func_name;
    m_args = move(args);
}

CallExpressionAST::~CallExpressionAST() {
}

const string &CallExpressionAST::get_func_name() const {
    return m_func_name;
}

const vector<unique_ptr<NodeAST>> &CallExpressionAST::get_args() const {
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
        args.push_back(arg->make_IR(scope));
        if (!args.back()) {
            return nullptr;
        }
    }

    return builder->CreateCall(func, args);
}

}