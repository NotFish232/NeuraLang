#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <assert.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

#include "AST/ast.hpp"

#include "lexer.hpp"
#include "token.hpp"

namespace nl {

class Parser {
private:
    const static std::map<std::string, int> binary_operator_precedence;

    std::vector<std::string> m_errors;
    std::fstream m_fileHandler;
    Lexer m_lexer;
    // std::map<std::string, llvm::Value *> m_values;

    llvm::Type *parse_type_expression();

    BlockAST parse_block_expression();
    BlockAST parse_bracket_block_expression();
    BlockAST parse_single_line_block_expression();

    FunctionAST parse_function_expression();
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
