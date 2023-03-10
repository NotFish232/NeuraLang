#include "../../../include/AST/conditional_logic/boolean_expression.hpp"

using namespace std;
using namespace llvm;

namespace nl {

BooleanExpressionAST::BooleanExpressionAST(unique_ptr<NodeAST> &left, unique_ptr<NodeAST> &right, const string &op) {
    m_left = move(left);
    m_right = move(right);
    m_operator = op;
}

BooleanExpressionAST::~BooleanExpressionAST() {
}

const unique_ptr<NodeAST> &BooleanExpressionAST::get_left() const {
    return m_left;
}

const unique_ptr<NodeAST> &BooleanExpressionAST::get_right() const {
    return m_right;
}

const string &BooleanExpressionAST::get_operator() const {
    return m_operator;
}

Value *BooleanExpressionAST::make_IR(ValueMap &scope) const {
    Value *left_IR = m_left->make_IR(scope);
    Value *right_IR = m_right->make_IR(scope);

    if (!left_IR || !right_IR) {
        return nullptr;
    }

    if (m_operator == "==") {
        return builder->CreateFCmpUEQ(left_IR, right_IR);
    } else if (m_operator == "!=") {
        return builder->CreateFCmpUNE(left_IR, right_IR);
    } else if (m_operator == "<") {
        return builder->CreateFCmpUGT(left_IR, right_IR);
    } else if (m_operator == "<=") {
        return builder->CreateFCmpULT(left_IR, right_IR);
    } else if (m_operator == ">") {
        return builder->CreateFCmpUGT(left_IR, right_IR);
    } else if (m_operator == ">=") {
        return builder->CreateFCmpUGE(left_IR, right_IR);
    } else {
        return nullptr;
    }
}

}