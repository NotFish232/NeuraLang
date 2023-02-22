#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "exprAST.hpp"
#include "prototypeAST.hpp"

// function syntax tree
// this represents the function itself.

llvm::Function *make_function_IR(std::unique_ptr<Value *> m_proto, )
class FunctionAST {
    std::unique_ptr<PrototypeAST> m_proto;
    std::unique_ptr<ExprAST> m_body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> m_proto, std::unique_ptr<ExprAST> m_body);
    llvm::Function *codegen();
};

#endif
