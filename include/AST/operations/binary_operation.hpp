#ifndef BINARYOPERATION_HPP
#define BINARYOPERATION_HPP

#include "../node.hpp"

// syntax tree for binary i.e. 1 + 2

namespace nl {

class BinaryOperationAST : public NodeAST {
    std::unique_ptr<NodeAST> m_left, m_right;
    std::string m_operator;

public:
    BinaryOperationAST(std::unique_ptr<NodeAST> &left,
                       std::unique_ptr<NodeAST> &right,
                       const std::string &op);
    ~BinaryOperationAST();

    const std::unique_ptr<NodeAST> &get_left() const;
    const std::unique_ptr<NodeAST> &get_right() const;
    const std::string &get_operator() const;
    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif
