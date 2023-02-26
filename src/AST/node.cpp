#include "../../include/AST/node.hpp"

using namespace std;
using namespace llvm;

namespace nl {

unique_ptr<NodeAST> NodeAST::null = make_unique<NodeAST>();

NodeAST::~NodeAST() {

}

Value *NodeAST::make_IR(ValueMap &scope) const {
    return nullptr;
}

}