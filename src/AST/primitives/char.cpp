#include "../../../include/AST/primitives/char.hpp"

using namespace std;
using namespace llvm;

namespace nl {

const size_t CharAST::default_num_bits = 8;

CharAST::CharAST(const string &value, size_t numBits) {
    m_value = value;
    m_numBits = numBits;
}

CharAST::~CharAST() {
}

const string &CharAST::get_value() const {
    return m_value;
}

Value *CharAST::make_IR() {
    return ConstantInt::get(*ctx, APInt(m_numBits, m_value, 10));
}

}