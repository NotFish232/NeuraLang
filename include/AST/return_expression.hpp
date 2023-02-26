#ifndef RETURNEXPRESSION_HPP
#define RETURNEXPRESSION_HPP

#include "node.hpp"

namespace nl {

class ReturnExpressionAST : public NodeAST {
private:
    std::unique_ptr<NodeAST> m_return_value;

public:
    ReturnExpressionAST(std::unique_ptr<NodeAST> &return_value);
    ~ReturnExpressionAST();
    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif