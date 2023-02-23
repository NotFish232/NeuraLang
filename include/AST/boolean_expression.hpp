#ifndef BINARYOPERATION_HPP
#define BINARYOPERATION_HPP

#include "node_ast.hpp"

// syntax tree for boolean expression


namespace nl {

class BooleanExpression : public NodeAST {
    std::unique_ptr<NodeAST> m_left, m_right;
    std::string m_operator;

public:
    BooleanExpression(std::unique_ptr<NodeAST> left, std::unique_ptr<NodeAST> right, const std::string &op);
    ~BooleanExpression();
    const std::unique_ptr<NodeAST> &get_left() const;
    const std::unique_ptr<NodeAST> &get_right() const;
    const std::string &get_operator() const;
    llvm::Value *make_IR() override;
};

};

#endif