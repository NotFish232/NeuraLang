#include "../../include/AST/node.hpp"

using namespace std;
using namespace llvm;
#include <iostream>

namespace nl {

NodeAST::~NodeAST() {

}

Value *NodeAST::make_IR(ValueMap &scope) const {
    cout << "im in base ir \n";
    return nullptr;
}

}