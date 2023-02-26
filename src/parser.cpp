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
        m_lexer.get_next(); // eat ':'
        flags.push_back(m_lexer.get_next().value);
    }

 

    if (type_str.value == "int") {
        return Type::getInt32Ty(*ctx);
    } else if (type_str.value == "float") {
        return Type::getDoubleTy(*ctx);
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

    vector<unique_ptr<NodeAST>> block;

    while (m_lexer.peek_next().value != "}") {
        block.push_back(parse_expression());
    }

    assert(m_lexer.get_next().value == "}"); // eats other bracket

    return block;
}

vector<unique_ptr<NodeAST>> Parser::parse_single_line_block_expression() {
    size_t line_num = m_lexer.peek_next().line_num;

    vector<unique_ptr<NodeAST>> block;

    while (m_lexer.peek_next().line_num == line_num) {
        block.push_back(parse_expression());
    }

    return block;
}

unique_ptr<NodeAST> Parser::parse_declaration() {
    // get the type of the function
    Type *type = parse_type_expression();

    // get the name of the function
    Token identifier_tok = m_lexer.get_next();
    assert(identifier_tok);

    if (m_lexer.peek_next().value == "(") {
        // if next token is a ( handle it as a function declaration
        return parse_function_declaration(type, identifier_tok.value);
    } else {
        // else handle it as a variable declaration
        return parse_variable_declaration(type, identifier_tok.value);
    }
}

unique_ptr<NodeAST> Parser::parse_variable_declaration(Type *type, const string &identfier) {
}

unique_ptr<FunctionAST> Parser::parse_function_declaration(Type *return_type, const string &identfier) {
    assert(m_lexer.get_next().value == "("); // eats (
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

    auto func_sig = make_unique<FunctionSignatureAST>(identfier, args, return_type);

    vector<unique_ptr<NodeAST>> body = parse_block_expression();
    
    return make_unique<FunctionAST>(func_sig, body);
}

unique_ptr<ForLoopAST> Parser::parse_for_expression() {
}

unique_ptr<WhileLoopAST> Parser::parse_while_expression() {
}

unique_ptr<IfStatementAST> Parser::parse_if_expression() {
}

unique_ptr<NodeAST> Parser::parse_expression() {
    Token tok = m_lexer.peek_next();

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
            return parse_declaration();
            cout << "I parsed a declaration \n";
        } else {
            cout << "error unrecognized expression \n";
        }
    }
}

void Parser::build_AST() {
    while (m_lexer.has_next()) {
        m_ast.push_back(parse_expression());
    }
    cout << "Finished building AST \n";
}

void Parser::generate_IR() {
    m_lexer.parse_tokens();

    build_AST();

    for (auto &node: m_ast) {
        node->make_IR(m_global_scope);
    }

    // gen ir
    // add main func
    cout << "Finished generating IR \n";
}
}