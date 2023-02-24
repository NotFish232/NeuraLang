#include "../../include/AST/block.hpp"

using namespace std;
using namespace llvm;

namespace nl {

BlockAST::BlockAST() {

}

BlockAST::~BlockAST() {

}

void BlockAST::add(NodeAST expr) {
    m_contents.push_back(expr);
}

Value *BlockAST::make_IR() const {
    return nullptr;
}

}