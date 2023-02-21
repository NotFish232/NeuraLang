#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

namespace nl {

enum class TokenType {
    keyword,    // i.e. def if else for while etc
    identifier, // i.e. a variable
    number,
    string,
    symbol,     // [](){}|+-*/&&|| etc
    null
};

struct Token {
    // a null value token that can be returned from functions that require a const &
    static const Token null;
    TokenType type;
    std::string value;
    size_t line_num;
};

std::string repr(const TokenType &t);
std::ostream &operator<<(std::ostream &os, const TokenType &t);
std::ostream &operator<<(std::ostream &os, const Token &token);

}

#endif
