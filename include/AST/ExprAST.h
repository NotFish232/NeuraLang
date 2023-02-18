//
// Created by piuslee on 2/18/23.
//

#ifndef EXPRAST_H
#define EXPRAST_H

#include "llvm/IR/BasicBlock.h"

//base class for all
class ExprAST {
    public: virtual ~ExprAST() {} //virtual meaning a subclass can override this implentation
    virtual llvm::Value *codegen() = 0;
};

#endif
