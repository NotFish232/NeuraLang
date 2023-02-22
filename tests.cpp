#define assert(condition)                                                                                      \
    do {                                                                                                       \
        if (condition) {                                                                                       \
            cout << GREEN "[SUCCESS]" RESET " Assertion `" #condition "` succeeded! \n";                       \
            passingTests++;                                                                                 \
        } else {                                                                                               \
            cout << RED "[FAILURE]" RESET " Assertion `" #condition "` failed on line " << __LINE__ << ". \n"; \
        }                                                                                                      \
        totalTest++;                                                                                         \
    } while (false)

#include "include/parser.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv){
    using namespace nl;
    Parser parser("examples/functions.nl");
    parser.load_module("IR/std.ll");
}