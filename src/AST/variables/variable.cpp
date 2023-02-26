#include "../../../include/AST/variables/variable.hpp"

using namespace std;
using namespace llvm;

namespace nl {

VariableAST::VariableAST(const string &name, Type *type) {
    m_name = name;
    m_type = type;
}

VariableAST::~VariableAST() {
}

const string &VariableAST::get_name() const {
    return m_name;
}

Type *VariableAST::get_type() const {
    return m_type;
}

Value *VariableAST::make_IR(ValueMap &scope) const {
    return scope.find(m_name) != scope.end() ?  scope[m_name] : nullptr;
}

}