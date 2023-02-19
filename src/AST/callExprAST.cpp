//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/callExprAST.hpp"

using namespace std;
using namespace llvm;

CallExprAST::CallExprAST(const string &funcName, vector<unique_ptr<ExprAST>> args)
    : m_funcName(funcName), m_args(move(args)) {}

Value *CallExprAST::codegen() {
    Function *FunctionCallee = mod->getFunction(m_funcName);

    if (!FunctionCallee) {
        Logger::error("Unknown function referenced");
        return nullptr;
    }

    if (FunctionCallee->arg_size() != m_args.size()) {
        Logger::error("Incorrect # arguments passed");
        return nullptr;
    }

    vector<Value *> ArgsV;
    for (unsigned i = 0, e = m_args.size(); i != e; i++) {
        ArgsV.push_back(m_args[i]->codegen());

        if (!ArgsV.back()) {
            return nullptr;
        }
    }

    return builder.CreateCall(FunctionCallee, ArgsV, "calltmp");
}