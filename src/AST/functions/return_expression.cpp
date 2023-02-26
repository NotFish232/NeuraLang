#include "../../../include/AST/functions/return_expression.hpp"

using namespace std;
using namespace llvm;

namespace nl {

ReturnExpressionAST::ReturnExpressionAST(unique_ptr<NodeAST> &return_value) {
    m_return_value = move(return_value);
}

ReturnExpressionAST::~ReturnExpressionAST() {
}

Value *ReturnExpressionAST::make_IR(ValueMap &scope) const {
    return ReturnInst::Create(*ctx, m_return_value->make_IR(scope));
}

}