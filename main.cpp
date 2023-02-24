#include "include/parser.hpp"
#include <iostream>

using namespace std;
using namespace nl;
using namespace llvm;

int main(int argc, char **argv) {

    //Lexer lexer; fstream f("examples/functions.nl", ios::in); lexer.set_stream(f); lexer.parse_tokens();  while (lexer.has_next()) cout << lexer.get_next() << '\n';
    string filename = "examples/functions.nl";

    Parser parser(filename);
    parser.generate_IR();

    return EXIT_SUCCESS;
}