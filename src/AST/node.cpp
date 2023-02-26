#include "../../include/AST/node.hpp"

using namespace std;
using namespace llvm;

namespace nl {

NodeAST::~NodeAST() {

}

Value *NodeAST::make_IR(ValueMap &scope) const {
    return nullptr;
}

}