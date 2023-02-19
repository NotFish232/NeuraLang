//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/numberExprAST.hpp"

using namespace std;
using namespace llvm;

NumberExprAST::NumberExprAST(double val): m_val(val) {}

Value *NumberExprAST::codegen() {
    return ConstantFP::get(*ctx, APFloat(m_val));
}