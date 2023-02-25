#ifndef PARSER_HPP
#define PARSER_HPP

#include <assert.h>
#include <map>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

#include "AST/ast.hpp"

#include "constants.hpp"
#include "lexer.hpp"
#include "token.hpp"

namespace nl {

class Parser {
private:
    ValueMap m_global_scope;
    NodeAST d;

    std::fstream m_file_handle;
    Lexer m_lexer;

    std::vector<std::string> m_errors;

    FunctionAST make_main_function();

    llvm::Type *parse_type_expression();

    std::vector<NodeAST> parse_block_expression();
    std::vector<NodeAST> parse_bracket_block_expression();
    std::vector<NodeAST> parse_single_line_block_expression();

    /**
     * @note declaration is either a function or variable declaration
     */
    NodeAST parse_declaration();

    FunctionAST parse_function_expression();
    NodeAST parse_variable_expression();

    void parse_for_expression();
    void parse_while_expression();
    IfExpressionAST parse_if_expression();
    NodeAST parse_expression();

public:
    Parser(const std::string &filename);
    ~Parser();
    void generate_IR();
};

}

#endif
