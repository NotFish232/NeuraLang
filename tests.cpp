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
    ifstream f("examples/functions.nl", ios::in);
    Lexer lexer(f);
    lexer.parse_tokens();
    while (lexer.has_next()) {
        cout << lexer.get_next_token() << '\n';
    }
    return 0;    
}