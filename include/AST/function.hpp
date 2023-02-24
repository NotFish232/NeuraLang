#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "node.hpp"
#include "block.hpp"
#include "function_signature.hpp"

namespace nl {

class FunctionAST: public NodeAST {
    FunctionSignatureAST m_signature;
    BlockAST m_body;

public:
    FunctionAST(FunctionSignatureAST signature, BlockAST body);
    ~FunctionAST();

    const FunctionSignatureAST &get_signature() const;
    const BlockAST &get_body() const;
    llvm::Function *make_IR() const override;
};

}

#endif
