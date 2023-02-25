#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "node.hpp"
#include "function_signature.hpp"
#include "return_expression.hpp"

namespace nl {

class FunctionAST: public NodeAST {
    FunctionSignatureAST m_signature;
    std::vector<NodeAST> m_content;

public:
    FunctionAST(FunctionSignatureAST signature, std::vector<NodeAST> content);
    ~FunctionAST();

    const FunctionSignatureAST &get_signature() const;
    const std::vector<NodeAST> &get_content() const;
    llvm::Function *make_IR(ValueMap &scope) const override;
};

}

#endif
