#include <iostream>
#include "include/parser.hpp"

using namespace std;
using namespace nl;
using namespace llvm;

int main(int argc, char **argv) {
    ctx = std::make_unique<LLVMContext>();
    mod = std::make_unique<Module>("JIT", *ctx);
    builder = std::make_unique<IRBuilder<>>(*ctx);

    Parser parser("examples/hello_world.nl");
    parser.parse();

    return EXIT_SUCCESS;
}