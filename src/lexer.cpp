#include "../include/lexer.hpp"

using namespace std;
using namespace nl;

Lexer::Lexer(istream &inputStream): m_inputStream(inputStream) {
}

Token Lexer::getToken() {
    char lastChar = ' ';

    while (isspace(lastChar) && !m_inputStream.eof()) {
        m_inputStream.get(lastChar);
    }

    if (m_inputStream.eof()) {
        return Token{TokenType::_eof, "", 0};
    }

    if (isalpha(lastChar)) {
        string identifier = "";

        do {
            identifier += lastChar;
            m_inputStream.get(lastChar);
        } while (isalpha(lastChar));

        if (identifier == "def") {
            return Token{TokenType::_def, "", 0};
        }

        if (identifier == "extern") {
            return Token{TokenType::_extern, "", 0};
        }

        return Token{TokenType::_unknownIdentifier, identifier, 0};
    }

    // Stacking together only numeric values
    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;

        do {
            numStr += lastChar;
            m_inputStream.get(lastChar);
        } while (isdigit(lastChar) || lastChar == '.');

        return Token{TokenType::_number, "", strtod(numStr.c_str(), 0)};
    }

    if (lastChar == '#') {
        do {
            m_inputStream.get(lastChar);
        } while (!m_inputStream.eof() && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF) {
            return getToken();
        }
    }

    return Token{TokenType::_unknownToken, "" + lastChar, 0};
}
