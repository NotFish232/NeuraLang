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

#include "include/lexer.hpp"

int main(int argc, char **argv){
    int passingTests = 0, totalTests = 0;

    using namespace nl;

    Lexer lexer("examples/hello_world.nl");

    Token token;
}