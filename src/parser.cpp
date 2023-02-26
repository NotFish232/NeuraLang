#include "../include/parser.hpp"

using namespace std;
using namespace llvm;

namespace nl {

Parser::Parser(const string &filename) {
    m_file_handle = fstream(filename, ios::in);
    if (!m_file_handle.good()) {
        throw new runtime_error("Could not open file \"" + filename + "\"");
    }
    m_lexer.set_stream(m_file_handle);
    make_main_function()->make_IR(m_global_scope)->dump();
    cout << "hi \n";
}

Parser::~Parser() {
}

unique_ptr<FunctionAST> Parser::make_main_function() {
    vector<unique_ptr<VariableAST>> args;
    Type *ret_type = Type::getInt32Ty(*ctx);
    unique_ptr<FunctionSignatureAST> func_sig = make_unique<FunctionSignatureAST>("main", args, ret_type);
    vector<unique_ptr<NodeAST>> body;
    unique_ptr<NodeAST> ret_val = make_unique<NumberAST>("0");
    unique_ptr<ReturnExpressionAST> ret = make_unique<ReturnExpressionAST>(ret_val);
    body.push_back(move(ret));
    
    return make_unique<FunctionAST>(func_sig, body);
    /*
    vector<unique_ptr<VariableAST>> args;
    Type *ret_type = Type::getInt32Ty(*ctx);
    unique_ptr<FunctionSignatureAST> func_sig = make_unique<FunctionSignatureAST>("main", args, ret_type);
    vector<unique_ptr<NodeAST>> v;
    unique_ptr<NumberAST> ret_val = make_unique<NumberAST>("0");
    unique_ptr<ReturnExpressionAST> ret = make_unique<ReturnExpressionAST>(ret_val);
    v.push_back(move(ret));
    
    return make_unique<FunctionAST>(func_sig, v);*/
    return nullptr;
}



Type *Parser::parse_type_expression() {
    Token type_str = m_lexer.get_next();
    assert(type_str);

    // e.g. int:64:s or int:64:128:32:u
    vector<string> flags;
    while (m_lexer.peek_next().value == ":") {
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

vector<unique_ptr<NodeAST>> Parser::parse_block_expression() {
    if (m_lexer.peek_next().value == "{") {
        return parse_bracket_block_expression();
    } else {
        return parse_single_line_block_expression();
    }
}

vector<unique_ptr<NodeAST>> Parser::parse_bracket_block_expression() {
    assert(m_lexer.get_next().value == "{"); // eats bracket
}

vector<unique_ptr<NodeAST>> Parser::parse_single_line_block_expression() {
}

unique_ptr<NodeAST> Parser::parse_declaration() {
}

unique_ptr<NodeAST> Parser::parse_variable_expression() {
}

unique_ptr<FunctionAST> Parser::parse_function_expression() {/*
    // eat def keyword
    // and get next token which is func name
    Token function_name = m_lexer.get_next();
    cout << function_name << '\n';

    assert(function_name);

    assert(m_lexer.get_next().value == "(");

    vector<unique_ptr<VariableAST>> args;

    while (m_lexer.peek_next().value != ")") {
        Type *type = parse_type_expression();

        Token param_name = m_lexer.get_next();
        assert(param_name);

        assert(m_lexer.peek_next().value == "," || m_lexer.peek_next().value == ")");

        if (m_lexer.peek_next().value == ",")
            // eat comma
            m_lexer.get_next();

        auto var = make_unique<VariableAST>(param_name.value, type);

        args.push_back(move(var));
    }

    assert(m_lexer.get_next().value == ")");
    assert(m_lexer.get_next().value == "->");

    Type *return_type = parse_type_expression();

    FunctionSignatureAST func_sig(function_name.value, args, return_type);

    vector<unique_ptr<NodeAST>> body = parse_block_expression();

    return make_unique<FunctionAST>(func_sig, body);*/
}

void Parser::parse_for_expression() {
}

void Parser::parse_while_expression() {
}

unique_ptr<IfExpressionAST> Parser::parse_if_expression() {
}

unique_ptr<NodeAST> Parser::parse_expression() {
    Token tok = m_lexer.peek_next();

    cout << tok << '\n';

    if (tok.type == TokenType::keyword) {
        if (tok.value == "for") {
            parse_for_expression();
        } else if (tok.value == "while") {
            parse_while_expression();
        } else if (tok.value == "if") {
            parse_if_expression();
        } else {
            cout << "Unrecognized keyword \"" << tok.value << "\"\n";
        }
    } else {
        if (core_types.find(tok.value) != core_types.end()) {
            parse_declaration();
        } else {
            cout << "error unrecognized expression \n";
        }
    }
}

void Parser::generate_IR() {
    make_main_function();
    return;
    m_lexer.parse_tokens();
    while (m_lexer.has_next()) {
        parse_expression();
    }
}
}