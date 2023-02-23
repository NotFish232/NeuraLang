#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <set>
#include <vector>

#include "token.hpp"

namespace nl {

class Lexer {
private:
    const static std::set<std::string> keywords;
    const static std::set<std::string> valid_long_symbols;

    std::istream *m_inputStream;
    std::vector<Token> m_tokens;
    size_t m_tokenIndex;

public:
    Lexer();
    Lexer(std::istream &inputStream);
    ~Lexer();

    void set_stream(std::istream &inputStream);

    bool has_next() const;
    const Token &get_curr() const;
    const Token &peek_next() const;
    const Token &get_next();

    void parse_tokens();
};

}

#endif