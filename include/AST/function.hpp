#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "node.hpp"
#include "block.hpp"
#include "function_signature.hpp"

namespace nl {

class FunctionAST: public NodeAST {
    std::unique_ptr<FunctionSignatureAST> m_signature;
    std::unique_ptr<BlockAST> m_body;

public:
    FunctionAST(std::unique_ptr<FunctionSignatureAST> sig, std::unique_ptr<BlockAST> body);
    ~FunctionAST();

    const std::unique_ptr<FunctionSignatureAST> &get_signature() const;
    const std::unique_ptr<BlockAST> &get_body() const;
    llvm::Function *make_IR() override;
};

}

#endif
