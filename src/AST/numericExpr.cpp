//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/numericExprAST.hpp"

using namespace std;
using namespace llvm;

NumericExprAST::NumericExprAST(double val): m_val(val) {}

Value *NumericExprAST::codegen() {
    return ConstantFP::get(*ctx, APFloat(m_val));
}