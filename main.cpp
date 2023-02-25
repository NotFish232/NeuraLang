#include "include/parser.hpp"
#include <iostream>

using namespace std;
using namespace nl;
using namespace llvm;

int main(int argc, char **argv) {
    map<string, Value*> m;
    NumberAST("").make_IR(m);
    ReturnExpressionAST(NumberAST("")).make_IR(m); return 0;

    // NodeAST * thing = new ReturnExpressionAST(NumberAST(""));

    // cout << dynamic_cast<ReturnExpressionAST *>(thing) << '\n'; return 0;

    // Lexer lexer; fstream f("examples/functions.nl", ios::in); lexer.set_stream(f); lexer.parse_tokens();  while (lexer.has_next()) cout << lexer.get_next() << '\n';
    string filename = "examples/functions.nl";
    string outfile = "out.ll";
    Parser parser(filename);

    freopen(outfile.c_str(), "w", stderr);
    mod->dump();
    // parser.generate_IR();

    return EXIT_SUCCESS;
}