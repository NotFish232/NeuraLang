//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/binaryExprAST.hpp"

using namespace std;
using namespace llvm;

BinaryExprAST::BinaryExprAST(char op, unique_ptr<ExprAST> left, unique_ptr<ExprAST> right)
: m_operator(op), m_left(move(left)), m_right(move(right)) {}

Value *BinaryExprAST::codegen() {
    Value *L = m_left->codegen();
    Value *R = m_right->codegen();

    if (!L || !R) return nullptr;

    switch (m_operator) {
        case '+':
            return builder.CreateFAdd(L, R, "addtmp");
        case '-':
            return builder.CreateFSub(L, R, "subtmp");
        case '*':
            return builder.CreateFMul(L, R, "multmp");
        case '<':
            L = builder.CreateFCmpULT(L, R, "cmptmp");
            return builder.CreateUIToFP(L, Type::getDoubleTy(ctx), "booltmp");
        default:
            Logger::error("Invalid binary operator");
            return nullptr;
    }
}