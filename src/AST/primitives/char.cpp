#include "../../../include/AST/primitives/char.hpp"

using namespace std;
using namespace llvm;

namespace nl {

const size_t CharAST::default_num_bits = 8;

CharAST::CharAST(const string &value, size_t num_bits) {
    m_value = value;
    m_num_bits = m_num_bits;
}

CharAST::~CharAST() {
}

const string &CharAST::get_value() const {
    return m_value;
}

Value *CharAST::make_IR(ValueMap &scope) const {
    return ConstantInt::get(*ctx, APInt(m_num_bits, m_value, 10));
}

}