#ifndef EXPR_HPP
#define EXPR_HPP

#include <llvm/IR/IRBuilder.h>

#include "../neuralang.hpp"

namespace nl {

// base class for all
class NodeAST {
public:
    virtual ~NodeAST() {}
    virtual llvm::Value *make_IR() = 0;
};

}

#endif
