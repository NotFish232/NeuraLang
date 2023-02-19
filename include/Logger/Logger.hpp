//
// Created by piuslee on 2/18/23.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../AST/ExprAST.hpp"
#include "../AST/PrototypeAST.hpp"

std::unique_ptr<ExprAST> LogError(const char *Str);
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);
llvm::Value *LogErrorV(const char *Str);

#endif
