#include "../include/lexer.hpp"
#include "../include/token.hpp"

using namespace std;

namespace nl {

const set<string> Lexer::keywords = {"def", "for", "while", "if", "else", "break", "continue", "return"};
const set<string> Lexer::valid_long_symbols = {"+=", "-=", "*=", "/=", "==", "!=", ">=", "<=", "->", "++", "--", "&&", "**"};

Lexer::Lexer() {
    m_tokenIndex = 0;
    m_inputStream = nullptr;
}

Lexer::Lexer(istream &inputStream) {
    m_tokenIndex = 0;
    m_inputStream = &inputStream;
}

Lexer::~Lexer() {
}

void Lexer::set_stream(istream &inputStream) {
    m_inputStream = &inputStream;
}

bool Lexer::has_next() const {
    return m_tokenIndex < m_tokens.size();
}

const Token &Lexer::get_curr() const {
    return m_tokenIndex != 0 ? m_tokens[m_tokenIndex - 1] : Token::null;
}

const Token &Lexer::peek_next() const {
    return has_next() ? m_tokens[m_tokenIndex] : Token::null;
}

const Token &Lexer::get_next() {
    return has_next() ? m_tokens[m_tokenIndex++] : Token::null;
}

void Lexer::parse_tokens() {
    if (m_inputStream == nullptr) {
        throw new runtime_error("Lexer's input stream must be set before parsing tokens.");
    }

    if (!m_inputStream->good()) {
        throw new runtime_error("Bad input stream");
    }

    size_t line_num = 1;
    for (string line; getline(*m_inputStream, line); ++line_num) {
        line += '\n'; // force code to parse token at end of line

        TokenType type = TokenType::null;
        string val = "";

        // whether or not line has started - necessary to ignore comments
        bool has_line_started = false;

        for (size_t i = 0; i < line.length(); ++i) {
            // ignore comments
            if (!has_line_started && line[i] == '#') {
                break;
            }

            char ch = line[i];

            if (type == TokenType::null) {
                // ignore spaces
                if (isspace(line[i])) {
                    continue;
                }

                has_line_started = true;

                if (ch == '"') {
                    type = TokenType::_str;
                    continue; // don't add quote to string
                } else if (ch == '\'') {
                    type = TokenType::_char;
                    continue; // same thing as with string
                } else if (isalpha(ch)) {
                    type = TokenType::identifier;
                } else if (isdigit(ch)) {
                    type = TokenType::_num;
                } else {
                    type = TokenType::symbol;
                }

                val += ch;
            } else {
                // clang-format off
                if (
                    (isspace(ch) && type != TokenType::_str && type != TokenType::_char) ||
                    (type == TokenType::_str && ch == '"') ||
                    (type == TokenType::_char && ch == '\'') ||
                    (type == TokenType::identifier && !isalpha(ch) && !isdigit(ch)) ||
                    (type == TokenType::_num && !isdigit(ch) && (ch != '.' || val.find('.') != string::npos)) ||
                    (type == TokenType::symbol && valid_long_symbols.find(val + line[i]) == valid_long_symbols.end())
                    ) { // clang-format on
                    /*
                    6 possible conditions that the identifier / number / symbol has ended
                        1. followed by a space, and is not a string or char
                        2. another double quote meaning string has ended
                        3. another single quote meaning character has ended
                        4. identifer string followed by a non alpha, not digit character
                        5. number is followed by NaN and either not a period or a period and it already has a period
                        6. adding the next character makes it not a valid symbol
                    */

                    if (type == TokenType::identifier && keywords.find(val) != keywords.end()) {
                        type = TokenType::keyword;
                    }

                    m_tokens.push_back({type, val, line_num});

                    if (type != TokenType::_str && type != TokenType::_char) {
                        // do not reprocess char if it is a string, i.e discard the quote
                        --i;
                    }
                    type = TokenType::null;
                    val.clear();

                } else {
                    val += ch;
                }
            }
        }
    }
}

}
