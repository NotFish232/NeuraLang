#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

namespace nl {

enum class TokenType {
    keyword,    // i.e. def if else for while etc
    identifier, // i.e. a variable
    _num,     // a number
    _char, // a char
    _str,     // a string
    symbol,     // [](){}|+-*/&&|| etc
    null        // placeholder value
};

struct Token {
    // a null value token that can be returned from functions that require a const &
    static const Token null;
    TokenType type;
    std::string value;
    size_t line_num;

    operator bool() const;
};

std::string repr(const TokenType &t);
std::ostream &operator<<(std::ostream &os, const TokenType &t);
std::ostream &operator<<(std::ostream &os, const Token &token);


}

#endif
