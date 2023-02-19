//
// Created by piuslee on 2/18/23.
//

#include "../include/neuraLang.hpp"

using namespace llvm;

// This is an object that owns LLVM core data structures
std::unique_ptr<LLVMContext> ctx;

// This is a helper object that makes easy to generate LLVM instructions
std::unique_ptr<IRBuilder<>> builder;

// This is an LLVM construct that contains functions and global variables
std::unique_ptr<Module> mod;

// This map keeps track of which values are defined in the current scope
std::map<std::string, Value *> values;

// This is the global logger
Logger logger;

