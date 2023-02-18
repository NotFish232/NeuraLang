//
// Created by piuslee on 2/18/23.
//

#ifndef NEURALLANG_HPP
#define NEURALLANG_HPP

#include "llvm/ADT/APFloat.hpp"
#include "llvm/ADT/STLExtras.hpp"
#include "llvm/IR/BasicBlock.hpp"
#include "llvm/IR/Constants.hpp"
#include "llvm/IR/DerivedTypes.hpp"
#include "llvm/IR/Function.hpp"
#include "llvm/IR/IRBuilder.hpp"
#include "llvm/IR/LLVMContext.hpp"
#include "llvm/IR/Module.hpp"
#include "llvm/IR/Type.hpp"
#include "llvm/IR/Verifier.hpp"
#include <map>

// This is an object that owns LLVM core data structures
extern llvm::LLVMContext ctx;

// This is a helper object that makes easy to generate LLVM instructions
extern llvm::IRBuilder<> builder;

// This is an LLVM construct that contains functions and global variables
extern std::unique_ptr<llvm::Module> module;

// This map keeps track of which values are defined in the current scope
extern std::map<std::string, llvm::Value *> valuesMaps;

#endif
