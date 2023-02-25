#include "../include/constants.hpp"

using namespace std;

namespace nl {

const set<string> keywords = {"for", "while", "if", "else", "break", "continue", "return"};
const set<string> valid_long_symbols = {
    "+=", "-=", "*=", "/=", "**=",        // arithmetic operations
    "^=", "|=", "&=", "~=", ">>=", "<<=", // bitewise operations
    "++", "--", "**",                     // dec, inc, square
    "==", "!=", ">=", "<=",               // comparison
    "->", "=>", "&&", "||"                // arrows and boolean gates
};
const set<string> core_types = {"int", "float", "char"};
// clang-format off
const map<string, int> binary_operator_precedence = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"^", 3},
    {"%", 3}
};
// clang-format on

}