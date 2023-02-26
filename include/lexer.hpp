#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <set>
#include <vector>

#include "token.hpp"
#include "constants.hpp"

namespace nl {

class Lexer {
private:
    std::istream *m_input_stream;
    std::vector<Token> m_tokens;
    long m_token_index;

public:
    Lexer();
    Lexer(std::istream &input_stream);
    ~Lexer();

    void set_stream(std::istream &input_stream);

    bool has_prev() const;
    bool has_next() const;

    const Token &get_curr() const;
    const Token &peek_prev() const;
    const Token &peek_next() const;

    const Token &get_prev();
    const Token &get_next();

    void parse_tokens();
};

}

#endif