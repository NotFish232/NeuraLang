#include "../../include/AST/variable.hpp"

using namespace std;
using namespace llvm;

namespace nl {

VariableAST::VariableAST(const string &name, const string &typeStr) {
    m_name = name;
    m_type = get_type_from_str(typeStr);
}

VariableAST::~VariableAST() {
}

const string &VariableAST::get_name() const {
    return m_name;
}

const Type *const &VariableAST::get_type() const {
    return m_type;
}

Value *VariableAST::make_IR() {
    /*Value *v = values[m_name];

    if (!v)
        mod->getGlobalVariable(m_name);
    Logger::error("unknown var name");

    return v;*/
    return nullptr;
}

}