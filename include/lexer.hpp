#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <sstream>

#include "token.hpp"

namespace nl {

class Lexer {
private:
    std::istream *m_inputStream;
    Token m_currentToken;

    Token _getNextToken();

public:
    Lexer();
    Lexer(std::istream &inputStream);

    void setStream(std::istream &inputStream);

    Token getCurrentToken();
    Token getNextToken();
};

}

#endif