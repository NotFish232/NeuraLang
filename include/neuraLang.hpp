#ifndef NEURALANG_HPP
#define NEURALANG_HPP

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <map>

namespace nl {

// This is an object that owns LLVM core data structures
extern std::unique_ptr<llvm::LLVMContext> ctx;

// This is a helper object that makes easy to generate LLVM instructions
extern std::unique_ptr<llvm::IRBuilder<>> builder;

// This is an LLVM construct that contains functions and global variables
extern std::unique_ptr<llvm::Module> mod;

// This map keeps track of which values are defined in the current scope
extern std::map<std::string, llvm::Value *> values;

}

#endif
