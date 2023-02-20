#ifndef STRINGEXPRAST_HPP
#define STRINGEXPRAST_HPP

#include "exprAST.hpp"

class StringExprAST : public ExprAST {
    std::string m_str;

public:
    // initializer list, assigns variable to class.  think getters & setters
    StringExprAST(const std::string &str);
    llvm::Value *codegen() override;
};

#endif
