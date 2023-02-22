#include "../../include/AST/type.hpp"

using namespace std;
using namespace llvm;

namespace nl {

Type *get_type_from_str(const string &typeStr, int n) {
    Type *type;
    if (typeStr == "float") {
        type = Type::getFloatTy(*ctx);
    } else if (typeStr == "double") {
        type = Type::getDoubleTy(*ctx);
    } else if (typeStr.front() == 'i') {
        int bits = stoi(typeStr.substr(1));
        type = Type::getIntNTy(*ctx, bits);
    } else if (typeStr == "char") {
        type = Type::getInt8Ty(*ctx);
    } else {
        throw new runtime_error("Unrecognized type \"" + typeStr + "\"");
    }
    
    if (n != -1) {
        type == ArrayType::get(type, n);
    }

    return type;
}

};