#ifndef BINARYOPERATION_HPP
#define BINARYOPERATION_HPP

#include "node.hpp"

// syntax tree for binary i.e. 1 + 2

namespace nl {

class BinaryOperationAST : public NodeAST {
    NodeAST m_left, m_right;
    std::string m_operator;

public:
    BinaryOperationAST(NodeAST left, NodeAST right, const std::string &op);
    ~BinaryOperationAST();
    const NodeAST &get_left() const;
    const NodeAST &get_right() const;
    const std::string &get_operator() const;
    llvm::Value *make_IR() const override;
};

}

#endif
