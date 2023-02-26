#include "../../../include/AST/functions/function.hpp"

using namespace std;
using namespace llvm;

namespace nl {

FunctionAST::FunctionAST(unique_ptr<FunctionSignatureAST> &signature, vector<unique_ptr<NodeAST>> &content) {
    m_signature = move(signature);
    m_content = move(content);
}

FunctionAST::~FunctionAST() {
}

const unique_ptr<FunctionSignatureAST> &FunctionAST::get_signature() const {
    return m_signature;
}

const vector<unique_ptr<NodeAST>> &FunctionAST::get_content() const {
    return m_content;
}

Function *FunctionAST::make_IR(ValueMap &scope) const {
    ValueMap function_scope(scope);
    Function *function = m_signature->make_IR(function_scope);

    string block_name = m_signature->get_name() + "_block";

    BasicBlock *block = BasicBlock::Create(*ctx, block_name, function);

    builder->SetInsertPoint(block);
    for (const auto &expr : m_content) {
        builder->Insert(expr->make_IR(function_scope));
    }

    scope[m_signature->get_name()] = function;

    return function;
}
}
