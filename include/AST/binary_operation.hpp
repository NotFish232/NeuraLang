#ifndef BINARYEXPRAST_HPP
#define BINARYEXPRAST_HPP

#include "node_ast.hpp"

// syntax tree for binary i.e. 1 + 2

namespace nl {

class BinaryOperation : public NodeAST {
    std::unique_ptr<NodeAST> m_left, m_right;
    std::string m_operator;

public:
    BinaryOperation(std::unique_ptr<NodeAST> left, std::unique_ptr<NodeAST> right, const std::string &op);
    ~BinaryOperation();
    const std::unique_ptr<NodeAST> &get_left() const;
    const std::unique_ptr<NodeAST> &get_right() const;
    const std::string &get_operator() const;
    llvm::Value *make_IR() override;
};

}

#endif
