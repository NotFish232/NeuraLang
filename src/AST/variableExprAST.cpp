//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/variableExprAST.hpp"

using namespace std;
using namespace llvm;

VariableExprAST::VariableExprAST(const string &name): m_name(name) {}

Value *VariableExprAST::codegen() {
    Value *v = values[m_name];

    if (!v)
        Logger::error("unknown var name");

    return v;
}