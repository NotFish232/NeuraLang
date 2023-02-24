#ifndef IFEXPRESSION_HPP
#define IFEXPRESSION_HPP

#include "block.hpp"
#include "boolean_expression.hpp"
#include "node.hpp"

namespace nl {

class IfExpressionAST : public NodeAST {
    BooleanExpressionAST m_condition;
    BlockAST m_then, m_else;

public:
    IfExpressionAST(BooleanExpressionAST condition,
                    BlockAST then_block,
                    BlockAST else_block);
    ~IfExpressionAST();

    llvm::Value *make_IR() const override;
};

}

#endif
