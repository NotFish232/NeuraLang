#include "../include/parser.hpp"

using namespace std;
using namespace llvm;

namespace nl {

// clang-format off
const map<string, int> Parser::binary_operator_precedence = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"^", 3},
    {"%", 3}
};
// clang-format on

Parser::Parser(const string &filename) {
    m_fileHandler = fstream(filename, ios::in);
    if (!m_fileHandler.good()) {
        throw new runtime_error("Could not open file \"" + filename + "\"");
    }
    m_lexer.set_stream(m_fileHandler);
}

Parser::~Parser() {
}

Type *Parser::parse_type_expression() {
    Token type_str = m_lexer.get_next();
    assert(type_str);

    if (type_str.value == "i") { // next token should be int
        Token num = m_lexer.get_next();
        assert(all_of(num.value.begin(), num.value.end(), ::isdigit));
        type_str.value += num.value;
    }

    if (type_str.value == "float") {
        return Type::getFloatTy(*ctx);
    } else if (type_str.value == "double") {
        return Type::getDoubleTy(*ctx);
    } else if (type_str.value.front() == 'i') {
        int bits = stoi(type_str.value.substr(1));
        return Type::getIntNTy(*ctx, bits);
    } else if (type_str.value == "char") {
        return Type::getInt8Ty(*ctx);
    } else {
        throw new runtime_error("Unrecognized type \"" + type_str.value + "\"");
    }
}

BlockAST Parser::parse_block_expression() {
    if (m_lexer.peek_next().value == "{") {
        return parse_bracket_block_expression();
    } else {
        return parse_single_line_block_expression();
    }
}

BlockAST Parser::parse_bracket_block_expression() {
    assert(m_lexer.get_next().value == "{"); // eats bracket


}

BlockAST Parser::parse_single_line_block_expression() {
}
FunctionAST Parser::parse_function_expression() {
    // eat def keyword
    // and get next token which is func name
    Token function_name = m_lexer.get_next();
    cout << function_name << '\n';

    assert(function_name);

    assert(m_lexer.get_next().value == "(");

    vector<VariableAST> args;

    while (m_lexer.peek_next().value != ")") {
        Type *type = parse_type_expression();

        Token param_name = m_lexer.get_next();
        assert(param_name);

        assert(m_lexer.peek_next().value == "," || m_lexer.peek_next().value == ")");

        if (m_lexer.peek_next().value == ",")
            // eat comma
            m_lexer.get_next();

        VariableAST var(param_name.value, type);

        args.push_back(var);
    }

    assert(m_lexer.get_next().value == ")");
    assert(m_lexer.get_next().value == "->");

    Type *return_type = parse_type_expression();

    FunctionSignatureAST func_sig(function_name.value, args, return_type);

    BlockAST body = parse_block_expression();

    return FunctionAST(func_sig, body);
}

void Parser::parse_for_expression() {
}

void Parser::parse_while_expression() {
}

IfExpressionAST Parser::parse_if_expression() {
}

NodeAST Parser::parse_expression() {
    size_t line_num = m_lexer.peek_next().line_num;
}

void Parser::generate_IR() {
    cout << "here \n";
    m_lexer.parse_tokens();
    cout << "here \n";
    while (m_lexer.has_next()) {
        Token tok = m_lexer.get_next();
        cout << tok << '\n';

        if (tok.type == TokenType::keyword) {
            if (tok.value == "def") {
                parse_function_expression();
                cout << "Finished parsing a function declaration \n";
            } else if (tok.value == "for") {
                parse_for_expression();
            } else if (tok.value == "while") {
                parse_while_expression();
            } else if (tok.value == "if") {
                parse_if_expression();
            } else {
                cout << "Unrecognized keyword \"" << tok.value << "\"\n";
            }
        } else {
            parse_expression();
        }
    }
}
}