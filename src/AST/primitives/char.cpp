#include "../../../include/AST/primitives/char.hpp"

using namespace std;
using namespace llvm;

namespace nl {

const size_t Char::default_num_bits = 8;

Char::Char(const string &value, size_t numBits) {
    m_value = value;
    m_numBits = numBits;
}

Char::~Char() {
}

const string &Char::get_value() const {
    return m_value;
}

Value *Char::make_IR() {
    return ConstantInt::get(*ctx, APInt(m_numBits, m_value, 10));
}

}