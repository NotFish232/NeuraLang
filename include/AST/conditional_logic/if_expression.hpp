#ifndef IFEXPRESSION_HPP
#define IFEXPRESSION_HPP

#include "boolean_expression.hpp"
#include "../node.hpp"

namespace nl {

class IfExpressionAST : public NodeAST {
    std::unique_ptr<BooleanExpressionAST> m_condition;
    std::vector<std::unique_ptr<NodeAST>> m_then, m_else;

public:
    IfExpressionAST(std::unique_ptr<BooleanExpressionAST> &condition,
                    std::vector<std::unique_ptr<NodeAST>> &then_block,
                    std::vector<std::unique_ptr<NodeAST>> &else_block);
    ~IfExpressionAST();

    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif
