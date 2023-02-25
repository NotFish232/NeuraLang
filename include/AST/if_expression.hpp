#ifndef IFEXPRESSION_HPP
#define IFEXPRESSION_HPP

#include "boolean_expression.hpp"
#include "node.hpp"

namespace nl {

class IfExpressionAST : public NodeAST {
    BooleanExpressionAST m_condition;
    std::vector<NodeAST> m_then, m_else;

public:
    IfExpressionAST(BooleanExpressionAST condition,
                    std::vector<NodeAST> then_block,
                    std::vector<NodeAST> else_block);
    ~IfExpressionAST();

    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif
