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
#include <iostream>

using namespace std;

int main(int argc, char **argv){
    using namespace nl;
    ifstream f("examples/hello_world.nl", ios::in);
    Lexer lexer(f);
    int i = 10;
    while (i--) {
        cout << lexer.getNextToken();
    }
    return 0;    
}