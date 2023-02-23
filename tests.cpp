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
   // Parser parser("examples/functions.nl");
   // parser.load_module("IR/std.ll");
   Lexer lexer;
   fstream f("examples/functions.nl", ios::in);
   lexer.set_stream(f);
   lexer.parse_tokens();
   while (lexer.has_next()) {
    cout << lexer.get_next() << '\n';
   }
   
}