#include "../../include/AST/block.hpp"

using namespace std;
using namespace llvm;

namespace nl {

BlockAST::BlockAST() {

}

BlockAST::~BlockAST() {

}

void BlockAST::add(unique_ptr<NodeAST> expr) {
    m_contents.push_back(move(expr));
}

Value *BlockAST::make_IR() {
    return nullptr;
}

}