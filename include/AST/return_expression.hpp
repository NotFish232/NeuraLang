#ifndef RETURNEXPRESSION_HPP
#define RETURNEXPRESSION_HPP

#include "node.hpp"

namespace nl {

class ReturnExpressionAST : public NodeAST {
private:
    NodeAST m_return_value;

public:
    ReturnExpressionAST(NodeAST return_value);
    ~ReturnExpressionAST();
    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif