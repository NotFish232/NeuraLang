#include "../include/neuralang.hpp"

using namespace std;
using namespace llvm;

namespace nl {

unique_ptr<LLVMContext> ctx = make_unique<LLVMContext>();
unique_ptr<IRBuilder<>> builder = make_unique<IRBuilder<>>(*ctx);
unique_ptr<Module> mod = make_unique<Module>("NeuraLang", *ctx);

}