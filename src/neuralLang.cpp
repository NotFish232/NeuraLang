//
// Created by piuslee on 2/18/23.
//

#include "../include/neuralLang.hpp"

using namespace std;
using namespace llvm;

// This is an object that owns LLVM core data structures
LLVMContext ctx;

// This is a helper object that makes easy to generate LLVM instructions
IRBuilder<> builder(ctx);

// This is an LLVM construct that contains functions and global variables
unique_ptr<Module> mod;

// This map keeps track of which values are defined in the current scope
map<string, Value *> values;

// This is the global logger
Logger logger;

