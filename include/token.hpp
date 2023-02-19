#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace nl {

enum class TokenType {
    _eof,
    _def,
    _extern,
    _identifier,
    _number,
    _unknownIdentifier,
    _unknownToken,
    _leftParen,
    _rightParen,
    _null
};

struct Token {
    TokenType type;
    std::string identifier;
    double numVal;
};

}

#endif
