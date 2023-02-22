#include "../../include/AST/string.hpp"

using namespace std;
using namespace llvm;

namespace nl {

StringAST::StringAST(const string &str) {
    m_str = str;
}

StringAST::~StringAST() {
}

const string &StringAST::get_str() const {
    return m_str;
}

Value *StringAST::make_IR() {
    return nullptr;
}

}