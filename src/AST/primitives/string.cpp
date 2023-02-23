#include "../../../include/AST/primitives/string.hpp"

using namespace std;
using namespace llvm;

namespace nl {

StringAST::StringAST(const string &value) {
    m_value = value;
}

StringAST::~StringAST() {
}

const string &StringAST::get_value() const {
    return m_value;
}

Value *StringAST::make_IR() {
    // return builder->CreateGlobalString(StringRef(m_str));
    return nullptr;
}

}