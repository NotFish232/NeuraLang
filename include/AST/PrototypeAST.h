//
// Created by piuslee on 2/18/23.
//

#ifndef PROTOTYPEAST_H
#define PROTOTYPEAST_H

#include "ExprAST.h"

//prototype function syntax tree, captures the name and the arguments
//basically represents the function, as a prototype.
class PrototypeAST {
    std::string Name;
    std::vector < std::string > Args;

public:
    PrototypeAST(const std::string & Name, std::vector < std::string > Args): Name(Name), Args(std::move(Args)) {}

    llvm::Function *codegen();
    const std::string & getName() const {
        return Name;
    }
};

#endif
