#include "include/parser.hpp"
#include <iostream>

using namespace std;
using namespace nl;
using namespace llvm;

int main(int argc, char **argv) {


    ctx = std::make_unique<LLVMContext>();
    mod = std::make_unique<Module>("JIT", *ctx);
    builder = std::make_unique<IRBuilder<>>(*ctx);

    string filename = "examples/hello_world.nl";
    if (argc != 1) {
        filename = argv[1];
    }

    Parser parser(filename);
    parser.parse();

    mod->print(errs(), nullptr);

    return EXIT_SUCCESS;
}