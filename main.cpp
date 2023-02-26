#include "include/parser.hpp"
#include <iostream>

using namespace std;
using namespace nl;
using namespace llvm;

int main(int argc, char **argv) {

    string filename = "examples/functions.nl";
    
    Parser parser(filename);

    parser.generate_IR();
    mod->dump();

    return EXIT_SUCCESS;
}