#include "../include/token.hpp"

using namespace std;

namespace nl {

const Token Token::null{TokenType::null};

string repr(const TokenType &t) {
    switch (t) {
    case TokenType::keyword:
        return "keyword";
    case TokenType::identifier:
        return "identifier";
    case TokenType::number:
        return "number";
    case TokenType::string:
        return "string";
    case TokenType::symbol:
        return "symbol";
    case TokenType::null:
        return "null";
    default:
        return "NA";
    }
}

ostream &operator<<(ostream &os, const TokenType &t) {
    return os << repr(t);
}

ostream &operator<<(ostream &os, const Token &token) {
    os << token.type << " - \"" << token.value << "\" (" << token.line_num << ")";
    return os;
}

}