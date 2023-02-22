#ifndef NEURALANG_HPP
#define NEURALANG_HPP

#include <llvm/IR/IRBuilder.h>

namespace nl {

extern std::unique_ptr<llvm::LLVMContext> ctx;
extern std::unique_ptr<llvm::IRBuilder<>> builder;
extern std::unique_ptr<llvm::Module> mod;

}

#endif