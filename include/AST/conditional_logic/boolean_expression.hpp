#ifndef BOOLEANOPERATION_HPP
#define BOOLEANOPERATION_HPP

#include "../node.hpp"

// syntax tree for boolean expression

namespace nl {

class BooleanExpressionAST : public NodeAST {
    std::unique_ptr<NodeAST> m_left, m_right;
    std::string m_operator;

public:
    BooleanExpressionAST(std::unique_ptr<NodeAST> &left,
                         std::unique_ptr<NodeAST> &right,
                         const std::string &op);
    ~BooleanExpressionAST();

    const std::unique_ptr<NodeAST> &get_left() const;
    const std::unique_ptr<NodeAST> &get_right() const;
    const std::string &get_operator() const;
    llvm::Value *make_IR(ValueMap &scope) const override;
};

};

#endif