#include "../../include/AST/binary_operation.hpp"

using namespace std;
using namespace llvm;

namespace nl {

BinaryOperationAST::BinaryOperationAST(unique_ptr<NodeAST> &left, unique_ptr<NodeAST> &right, const string &op) {
    m_left = move(left);
    m_right = move(right);
    m_operator = op;
}

BinaryOperationAST::~BinaryOperationAST() {
}

const unique_ptr<NodeAST> &BinaryOperationAST::get_left() const {
    return m_left;
}

const unique_ptr<NodeAST> &BinaryOperationAST::get_right() const {
    return m_right;
}

const string &BinaryOperationAST::get_operator() const {
    return m_operator;
}

Value *BinaryOperationAST::make_IR(ValueMap &scope) const {
    Value *left_IR = m_left->make_IR(scope);
    Value *right_IR = m_right->make_IR(scope);

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