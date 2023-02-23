#include "../../include/AST/function.hpp"

using namespace std;
using namespace llvm;

namespace nl {

FunctionAST::FunctionAST(unique_ptr<FunctionSignatureAST> sig, unique_ptr<BlockAST> body) {
    m_signature = move(sig);
    m_body = move(body);
}

FunctionAST::~FunctionAST() {

}

const unique_ptr<FunctionSignatureAST> &FunctionAST::get_signature() const {
    return m_signature;
}

const unique_ptr<BlockAST> &FunctionAST::get_body() const {
    return m_body;
}  

Function *FunctionAST::make_IR() {
    Function *function = m_signature -> make_IR();

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