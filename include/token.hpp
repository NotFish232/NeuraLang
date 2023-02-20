#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

namespace nl {

enum class TokenType {
    _eof,
    _def,
    _extern,
    _identifier,
    _number,
    _string,
    _unknownIdentifier,
    _unknownToken,
    _leftParen,
    _rightParen,
    _null,

    //add control flow
    _if,
    _then,
    _else
};

std::string repr(const TokenType &t);

struct Token {
    TokenType type;
    std::string identifier;
    double numVal;
};

std::ostream &operator<<(std::ostream &os, const TokenType &t);
std::ostream &operator<<(std::ostream &os, const Token &token);

}

#endif
