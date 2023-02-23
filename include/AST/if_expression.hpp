#ifndef IFEXPRESSION_HPP
#define IFEXPRESSION_HPP

#include "block.hpp"
#include "boolean_expression.hpp"
#include "node.hpp"

namespace nl {

class IfExpressionAST : public NodeAST {
    std::unique_ptr<BooleanExpressionAST> m_condition;
    std::unique_ptr<BlockAST> m_then, m_else;

public:
    IfExpressionAST(std::unique_ptr<BooleanExpressionAST> condition,
                    std::unique_ptr<BlockAST> then_block,
                    std::unique_ptr<BlockAST> else_block);
    ~IfExpressionAST();

    llvm::Value *make_IR() override;
};

}

#endif
