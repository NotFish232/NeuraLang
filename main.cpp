#include <iostream>
#include "include/parser.hpp"
#include <fstream>

int main(int argc, char **argv) {
    // Install standard binary operators.
    // 1 is lowest precedence.

    if (argc == 1) {
        return EXIT_FAILURE;
    }

    nl::Parser parser("examples/hello_world.nl");
    parser.parse();

    return EXIT_SUCCESS;

    mod->print(llvm::errs(), nullptr);



    return 0;
}