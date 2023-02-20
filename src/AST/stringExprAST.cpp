#include "../../include/AST/stringExprAST.hpp"

using namespace std;
using namespace llvm;

StringExprAST::StringExprAST(const string &str): m_str(str) {}

Value *StringExprAST::codegen() {
    return builder->CreateGlobalString(StringRef(m_str));
}