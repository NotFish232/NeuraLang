#include "../../include/AST/function.hpp"

using namespace std;
using namespace llvm;

namespace nl {

FunctionAST::FunctionAST(FunctionSignatureAST signature, BlockAST body): m_signature(signature) {
    m_body = body;
}

FunctionAST::~FunctionAST() {

}

const FunctionSignatureAST &FunctionAST::get_signature() const {
    return m_signature;
}

const BlockAST &FunctionAST::get_body() const {
    return m_body;
}  

Function *FunctionAST::make_IR() const {
    Function *function = m_signature.make_IR();

    if (!function)
        return nullptr;

    /*BasicBlock *block = BasicBlock::Create(*ctx, "entry", function);
    builder->SetInsertPoint(block);
    values.clear();

    for (auto &Arg : function->args()) {
        values[Arg.getName().data()] = &Arg;
    }

    if (Value *returnedValue = m_body->codegen()) {
        builder->CreateRet(returnedValue);
        verifyFunction(*function);

        return function;
    }

    function->eraseFromParent();*/
    return nullptr;
}

}