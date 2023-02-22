#include "../include/lexer.hpp"
#include "../include/token.hpp"

using namespace std;

namespace nl {

const set<string> Lexer::keywords = {"def", "for", "while", "if", "else", "break", "continue"};
// clang-format off
const set<string> Lexer::valid_symbols = {
    "=", "+", "+=", "-", "-=", "*", "*=", "/", "/=",
    "==", "!", "!=", ">", "<", ">=", "<=",
    ";", ",", ".", "\"", "'", "->",
    "(", ")", "[", "]", "{", "}"
};
// clang-format on

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
    return m_tokens.size() != 0 && m_tokenIndex < m_tokens.size();
}

const Token &Lexer::get_curr_token() const {
    return m_tokens[m_tokenIndex];
}

const Token &Lexer::get_next_token() {
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

            if (type == TokenType::null) {
                // ignore spaces
                if (isspace(line[i])) {
                    continue;
                }

                has_line_started = true;

                if (line[i] == '"') {
                    type = TokenType::string;
                    continue; // don't add quote to string
                } else if (isalpha(line[i])) {
                    type = TokenType::identifier;
                } else if (isdigit(line[i])) {
                    type = TokenType::number;
                } else {
                    type = TokenType::symbol;
                }

                val += line[i];
            } else {
                // clang-format off
                if (
                    (isspace(line[i]) && type != TokenType::string) ||
                    (type == TokenType::string && line[i] == '"') ||
                    (type == TokenType::identifier && !isalpha(line[i])) ||
                    (type == TokenType::number && !isdigit(line[i])) ||
                    (type == TokenType::symbol && valid_symbols.find(val + line[i]) == valid_symbols.end())
                    ) { // clang-format on
                    /*
                    3 possible conditions that the identifier / number / symbol has ended
                        1. followed by a space, and is not a string
                        2. another quote meaning string has ended
                        3. number is followed by NaN, doubles will be implemented later by AST
                        4. adding the next character makes it not a valid symbol
                    */

                    if (type == TokenType::identifier && keywords.find(val) != keywords.end()) {
                        type = TokenType::keyword;
                    }

                    m_tokens.push_back({type, val, line_num});

                    if (type != TokenType::string) {
                        // do not reprocess char if it is a string, i.e discard the quote
                        --i;
                    }
                    type = TokenType::null;
                    val.clear();

                } else {
                    val += line[i];
                }
            }
        }
    }
}

}
