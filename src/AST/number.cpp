#include "../../include/AST/number.hpp"

using namespace std;
using namespace llvm;

namespace nl {

NumberAST::NumberAST(const string &value, const string &type) {
    m_value = value;
    m_type = type;
}

NumberAST::~NumberAST() {
}

const string &NumberAST::get_value() const {
    return m_value;
}

const string &NumberAST::get_type() const {
    return m_type;
}

Value *NumberAST::make_IR() {
    // ints can be arbitrary precission
    if (m_type == "float") {
        return ConstantFP::get(*ctx, APFloat(stod(m_value)));
    } else if (m_type[0] == 'i') {
        size_t bits = stoi(m_type.substr(1));
        return ConstantInt::get(*ctx, APInt(bits, m_value, 10));
    } else {
        throw new runtime_error("Unrecognized type \"" + m_type + "\"");
    }
}

};
