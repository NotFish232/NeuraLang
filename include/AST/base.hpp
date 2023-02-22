#ifndef EXPR_HPP
#define EXPR_HPP

#include <llvm/IR/IRBuilder.h>

#include "../neuralang.hpp"

namespace nl {

// base class for all
class Base {
public:
    virtual ~Base() {} // virtual meaning a subclass can override this implentation
    virtual llvm::Value *make_IR() = 0;
};

}

#endif
