#include "../../../include/AST/primitives/number.hpp"

using namespace std;
using namespace llvm;

namespace nl {

NumberAST::NumberAST(const string &value) {
    m_value = value;
}

NumberAST::~NumberAST() {
}

const string &NumberAST::get_value() const {
    return m_value;
}


Value *NumberAST::make_IR(ValueMap &scope) const {
    // fix me figure out proper precision
    if (m_value.find(".") != string::npos) {
        return ConstantFP::get(*ctx, APFloat(stof(m_value)));
    } else {
        return ConstantInt::get(*ctx, APInt(32, m_value, 10));
    }
    // ints can be arbitrary precission
    /*if (m_type == "float") {
        return ConstantFP::get(*ctx, APFloat(stod(m_value)));
    } else if (m_type[0] == 'i') {
        size_t bits = stoi(m_type.substr(1));
        return ConstantInt::get(*ctx, APInt(bits, m_value, 10));
    } else {
        throw new runtime_error("Unrecognized type \"" + m_type + "\"");
    }*/
    return nullptr;
    
}

};
