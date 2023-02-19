//
// Created by piuslee on 2/18/23.
//

#include "../../include/AST/functionAST.hpp"

using namespace std;
using namespace llvm;

FunctionAST::FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<ExprAST> body) 
: m_proto(move(proto)), m_body(move(body)) {}

Function *FunctionAST::codegen() {
    Function *function = mod->getFunction(m_proto->getName());

    if (!function)
        function = m_proto->codegen();
    if (!function)
        return nullptr;

    BasicBlock *block = BasicBlock::Create(ctx, "entry", function);
    builder.SetInsertPoint(block);
    values.clear();

    for (auto &Arg : function->args()) {
        values[Arg.getName().data()] = &Arg;
    }

    if (Value *returnedValue = m_body->codegen()) {
        builder.CreateRet(returnedValue);
        verifyFunction(*function);

        return function;
    }

    function->eraseFromParent();
    return nullptr;
}