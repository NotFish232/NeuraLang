#include "../../include/AST/return_expression.hpp"

using namespace std;
using namespace llvm;

#include <iostream>
namespace nl {

ReturnExpressionAST::ReturnExpressionAST(NodeAST return_value) {
   m_return_value = return_value;
}

ReturnExpressionAST::~ReturnExpressionAST() {

}

Value *ReturnExpressionAST::make_IR(ValueMap &scope) const {
    cout << "in return expr make ir \n";
   return m_return_value.make_IR(scope);
}

}