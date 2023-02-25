#include "../../include/AST/function.hpp"

using namespace std;
using namespace llvm;
#include <iostream>
namespace nl {

FunctionAST::FunctionAST(FunctionSignatureAST signature, vector<NodeAST> content) : m_signature(signature) {
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

    string block_name = m_signature.get_name() + "_block";

    BasicBlock *block = BasicBlock::Create(*ctx, block_name, function);

    builder->SetInsertPoint(block);
    cout << m_content.size() << '\n';
    for (const auto &expr : m_content) {
        cout << "h \n";
        builder->CreateRet(expr.make_IR(function_scope));
        builder->Insert(expr.make_IR(function_scope));
    }
    //builder->CreateRet(ConstantFP::get(*ctx, APFloat(5.f)));
    //builder->ClearInsertionPoint();

    scope[m_signature.get_name()] = function;

    return function;
}
}
