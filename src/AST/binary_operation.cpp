#include "../../include/AST/binary_operation.hpp"

using namespace std;
using namespace llvm;

namespace nl {

BinaryOperationAST::BinaryOperationAST(NodeAST left, NodeAST right, const string &op) {
    m_left = left;
    m_right = right;
    m_operator = op;
}

BinaryOperationAST::~BinaryOperationAST() {
}

const NodeAST &BinaryOperationAST::get_left() const {
    return m_left;
}

const NodeAST &BinaryOperationAST::get_right() const {
    return m_right;
}

const string &BinaryOperationAST::get_operator() const {
    return m_operator;
}

Value *BinaryOperationAST::make_IR() const {
    Value *left_IR = m_left.make_IR();
    Value *right_IR = m_right.make_IR();

    if (m_operator == "+") {
        return builder->CreateFAdd(left_IR, right_IR);
    } else if (m_operator == "-") {
        return builder->CreateFSub(left_IR, right_IR);
    } else if (m_operator == "*") {
        return builder->CreateFMul(left_IR, right_IR);
    } else if (m_operator == "/") {
        return builder->CreateFDiv(left_IR, right_IR);
    } else if (m_operator == "^") {
        // builtin pow somehow
        return nullptr;
    } else if (m_operator == "%") {
        return nullptr;
    } else {
        return nullptr;
    }
}

}