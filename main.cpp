#include "include/parser.hpp"
#include <iostream>

using namespace std;
using namespace nl;
using namespace llvm;

int main(int argc, char **argv) {

    string filename = "examples/hello_world.nl";
    if (argc != 1) {
        filename = argv[1];
    }

    Parser parser(filename);
    parser.generate_IR();

    return EXIT_SUCCESS;
}