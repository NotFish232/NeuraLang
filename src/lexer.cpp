#include "../include/lexer.hpp"

using namespace std;
using namespace nl;

Lexer::Lexer(const string &filename) {
    m_inputStream = new ifstream(filename, ios::in);
}

Lexer::Lexer(istream &inputStream) {
    m_inputStream = &inputStream;
}

Token Lexer::getToken() {
    char lastChar = ' ';

    while (isspace(lastChar)) {
        m_inputStream->get(lastChar);
    }

    if (isalpha(lastChar)) {
        string identifier = "";

        do {
            identifier += lastChar;
            m_inputStream->get(lastChar);
        } while (isalpha(lastChar));

        if (identifier == "def") {
            return Token{TokenType::_def};
        }

        if (identifier == "extern") {
            return Token{TokenType::_extern};
        }

        return Token{TokenType::_unknownIdentifier, identifier};
    }

    // Stacking together only numeric values
    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;

        do {
            numStr += lastChar;
            m_inputStream->get(lastChar);
        } while (isdigit(lastChar) || lastChar == '.');

        return Token{TokenType::_number, "", strtod(numStr.c_str(), 0)};
    }

    if (lastChar == '#') {
        do {
            m_inputStream->get(lastChar);
        } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF)
            return getToken();
    }

    return Token{TokenType::_unknownToken, "" + lastChar};
}
