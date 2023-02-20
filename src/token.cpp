#include "../include/token.hpp"

using namespace std;

namespace nl {

string repr(const TokenType &t) {
    switch (t) {
    case TokenType::_eof:
        return "eof";
    case TokenType::_def:
        return "def";
    case TokenType::_extern:
        return "extern";
    case TokenType::_identifier:
        return "identifier";
    case TokenType::_number:
        return "number";
    case TokenType::_string:
        return "string";
    case TokenType::_unknownIdentifier:
        return "unknownIdentifier";
    case TokenType::_unknownToken:
        return "unknownToken";
    case TokenType::_leftParen:
        return "leftParen";
    case TokenType::_rightParen:
        return "rightParen";
    case TokenType::_null:
        return "null";
    default:
        return "NA";
    }
}

ostream &operator<<(ostream &os, const TokenType &t) {
    return os << repr(t);
}

ostream &operator<<(ostream &os, const Token &token) {
    os << token.type << ", " << token.identifier << ", " << token.numVal << '\n';
    return os;
}

}