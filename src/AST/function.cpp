#include "../../include/AST/function.hpp"

using namespace std;
using namespace llvm;
#include <iostream>
namespace nl {

FunctionAST::FunctionAST(FunctionSignatureAST signature, vector<NodeAST> content): 
m_signature(signature) {
    m_content = content;
}

FunctionAST::~FunctionAST() {
}

const FunctionSignatureAST &FunctionAST::get_signature() const {
    return m_signature;
}

const vector<NodeAST> &FunctionAST::get_content() const {
    return m_content;
}


Function *FunctionAST::make_IR(ValueMap &scope) const {
    ValueMap function_scope(scope);
    Function *function = m_signature.make_IR(function_scope);

    BasicBlock *block = BasicBlock::Create(*ctx, "func", function);

    builder->SetInsertPoint(block);
    if (m_content.size() != 0) {
        for (size_t i = 0; i < m_content.size() - 1; ++i) {
            builder->Insert(m_content[i].make_IR(function_scope));
        }
        builder->CreateRet(m_content.back().make_IR(function_scope));
    } else {
        builder->CreateRetVoid();
    }
    builder->ClearInsertionPoint();

    scope[m_signature.get_name()] = function;

    return function;
}
}
