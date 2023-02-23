#include "../include/parser.hpp"

using namespace std;
using namespace llvm;

namespace nl {

// clang-format off
const map<string, int> Parser::binary_operator_precedence = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"^", 3},
    {"%", 3}
};
// clang-format on

Parser::Parser(const string &filename) {
    m_fileHandler = fstream(filename, ios::in);
    if (!m_fileHandler.good()) {
        throw new runtime_error("Could not open file \"" + filename + "\"");
    }
    m_lexer.set_stream(m_fileHandler);

    m_lexer.parse_tokens();
}

Parser::~Parser() {
}

bool Parser::generate_IR() {
}

}