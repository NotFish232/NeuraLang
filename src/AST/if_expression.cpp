#include "../../include/AST/if_expression.hpp"

using namespace std;
using namespace llvm;

namespace nl {

IfExpressionAST::IfExpressionAST(unique_ptr<BooleanExpressionAST> condition, unique_ptr<BlockAST> then_block, unique_ptr<BlockAST> else_block) {
        m_condition = move(condition);
        m_then = move(then_block);
        m_else = move(else_block);

    }

IfExpressionAST::~IfExpressionAST() {

}

Value *IfExpressionAST::make_IR() {
    /*
    Value *condition = m_condition->codegen();
    if (!condition) return nullptr;

    // Convert condition to a bool by comparing equal to 0.0.
    condition = builder->CreateFCmpONE(condition, ConstantFP::get(*ctx, APFloat(0.0)), "ifcond");
    Function *function = builder->GetInsertBlock()->getParent();

    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    BasicBlock *thenBB = BasicBlock::Create(*ctx, "then", function);
    BasicBlock *elseBB = BasicBlock::Create(*ctx, "else");
    BasicBlock *mergedBB = BasicBlock::Create(*ctx, "ifcont");
    builder->CreateCondBr(condition, thenBB, elseBB);

    // Emit then value.
    builder->SetInsertPoint(thenBB);
    Value *ThenV = m_then->codegen();
    if (!ThenV) return nullptr;
    builder->CreateBr(mergedBB);

    // Codegen of '_then' can change the current block, update thenBB for the PHI.
    thenBB = builder->GetInsertBlock();

    // Emit else block.
    function->getBasicBlockList().push_back(elseBB);
    builder->SetInsertPoint(elseBB);
    Value *ElseV = m_else->codegen();
    if (!ElseV) return nullptr;
    builder->CreateBr(mergedBB);

    // Codegen of '_else' can change the current block, update elseBB for the PHI.
    elseBB = builder->GetInsertBlock();

    // Emit merge block.
    function->getBasicBlockList().push_back(mergedBB);
    builder->SetInsertPoint(mergedBB);
    PHINode *PN = builder->CreatePHI(Type::getDoubleTy(*ctx), 2, "iftmp");
    PN->addIncoming(ThenV, thenBB);
    PN->addIncoming(ElseV, elseBB);
    return PN;
    */
   return nullptr;
}

}