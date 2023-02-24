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
    case TokenType::_num:
        return "number";
    case TokenType::_str:
        return "string";
    case TokenType::_char:
        return "char";
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

Token::operator bool() const {
    return type != TokenType::null;
}

}