#include "../../include/AST/binary_operation.hpp"

using namespace std;
using namespace llvm;

namespace nl {

BinaryOperation::BinaryOperation(unique_ptr<NodeAST> left, unique_ptr<NodeAST> right, const string &op) {
    m_left = move(left);
    m_right = move(right);
    m_operator = op;
}

BinaryOperation::~BinaryOperation() {
}

const unique_ptr<NodeAST> &BinaryOperation::get_left() const {
    return m_left;
}

const unique_ptr<NodeAST> &BinaryOperation::get_right() const {
    return m_right;
}

const string &BinaryOperation::get_operator() const {
    return m_operator;
}

Value *BinaryOperation::make_IR() {
}

}