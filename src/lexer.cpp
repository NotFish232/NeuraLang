#include "../include/lexer.hpp"
#include "../include/token.hpp"

using namespace std;
using namespace nl;

Lexer::Lexer() {
    m_lastChar = ' ';
    m_inputStream = nullptr;
    m_currentToken = Token{TokenType::_null, "", 0};
}

Lexer::Lexer(istream &inputStream) {
    m_lastChar = ' ';
    m_inputStream = &inputStream;
    m_currentToken = Token{TokenType::_null, "", 0};
}

void Lexer::setStream(istream &inputStream) {
    m_inputStream = &inputStream;
}

Token Lexer::getCurrentToken() {
    return m_currentToken;
}

Token Lexer::getNextToken() {
    return m_currentToken = _getNextToken();
}

Token Lexer::_getNextToken() {
    char lastChar = m_lastChar;
    m_lastChar = ' ';
    while (isspace(lastChar) && !m_inputStream->eof()) {
        m_inputStream->get(lastChar);
    }

    if (m_inputStream->eof()) {
        return Token{TokenType::_eof, "", 0};
    }

    if (isalpha(lastChar)) {
        string identifier = "";

        do {
            identifier += lastChar;
            m_inputStream->get(lastChar);
        } while (isalpha(lastChar) && !m_inputStream->eof());
        m_lastChar = lastChar;

        if (identifier == "def") {
            return Token{TokenType::_def, "", 0};
        }

        if (identifier == "extern") {
            return Token{TokenType::_extern, "", 0};
        }

        return Token{TokenType::_identifier, identifier, 0};
    }

    // Stacking together only numeric values
    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;

        do {
            numStr += lastChar;
            m_inputStream->get(lastChar);
        } while ((isdigit(lastChar) || lastChar == '.') && !m_inputStream->eof());
        m_lastChar = lastChar;

        return Token{TokenType::_number, "", strtod(numStr.c_str(), 0)};
    }

    if (lastChar == '(') {
        return Token{TokenType::_leftParen, "(", 0};
    }
    if (lastChar == ')') {
        return Token{TokenType::_rightParen, ")", 0};
    }

    if (lastChar == '#') {
        do {
            m_inputStream->get(lastChar);
        } while (!m_inputStream->eof() && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF) {
            return _getNextToken();
        }
    }

    return Token{TokenType::_unknownToken, string(1, lastChar), 0};
}
