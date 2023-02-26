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
    std::fstream m_file_handle;
    Lexer m_lexer;

    ValueMap m_global_scope;

    std::vector<std::unique_ptr<NodeAST>> m_ast;

    std::unique_ptr<FunctionAST> make_main_function();

    llvm::Type *parse_type_expression();

    std::vector<std::unique_ptr<NodeAST>> parse_block_expression();
    std::vector<std::unique_ptr<NodeAST>> parse_bracket_block_expression();
    std::vector<std::unique_ptr<NodeAST>> parse_single_line_block_expression();

    /**
     * @note declaration is either a function or variable declaration
     */
    std::unique_ptr<NodeAST> parse_declaration();

    std::unique_ptr<FunctionAST> parse_function_declaration(llvm::Type *type, const std::string &identifier);
    std::unique_ptr<NodeAST> parse_variable_declaration(llvm::Type *return_type, const std::string &identifier);

    std::unique_ptr<ForLoopAST> parse_for_expression();
    std::unique_ptr<WhileLoopAST> parse_while_expression();

    std::unique_ptr<IfStatementAST> parse_if_expression();
    std::unique_ptr<NodeAST> parse_expression();

    void build_AST();

public:
    Parser(const std::string &filename);
    ~Parser();
    void generate_IR();
};

}

#endif
