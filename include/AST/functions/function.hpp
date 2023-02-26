#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "function_signature.hpp"
#include "../node.hpp"
#include "return_expression.hpp"

namespace nl {

class FunctionAST : public NodeAST {
    std::unique_ptr<FunctionSignatureAST> m_signature;
    std::vector<std::unique_ptr<NodeAST>> m_content;

public:
    FunctionAST(std::unique_ptr<FunctionSignatureAST> &signature,
                std::vector<std::unique_ptr<NodeAST>> &content);
    ~FunctionAST();

    const std::unique_ptr<FunctionSignatureAST> &get_signature() const;
    const std::vector<std::unique_ptr<NodeAST>> &get_content() const;
    llvm::Function *make_IR(ValueMap &scope) const override;
};

}

#endif
