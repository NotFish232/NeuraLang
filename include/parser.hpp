//
// Created by piuslee on 2/18/23.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>

#include "AST/binaryExprAST.hpp"
#include "AST/callExprAST.hpp"
#include "AST/exprAST.hpp"
#include "AST/functionAST.hpp"
#include "AST/numericExprAST.hpp"
#include "AST/prototypeAST.hpp"
#include "AST/variableExprAST.hpp"
#include "AST/ifExprAST.hpp"

#include "lexer.hpp"
#include "token.hpp"

namespace nl {

class Parser {
private:
    Lexer m_lexer;
    std::ifstream m_fileHandler;
    std::map<char, int> m_binopPrecedence;
    std::unique_ptr<ExprAST> parseNumberExpr();
    std::unique_ptr<ExprAST> parseParenExpr();
    std::unique_ptr<ExprAST> parseIdentifierExpr();
    std::unique_ptr<ExprAST> parsePrimary();
    std::unique_ptr<ExprAST> parseBinaryOperationRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
    std::unique_ptr<ExprAST> parseExpression();
    std::unique_ptr<PrototypeAST> parsePrototype();
    std::unique_ptr<FunctionAST> parseDefinition();
    std::unique_ptr<FunctionAST> parseTopLevelExpr();
    std::unique_ptr<PrototypeAST> parseExtern();
    std::unique_ptr<IfExprAST> parseIfExpr();
    void handleDefinition();
    void handleExtern();
    void handleTopLevelExpression();
    int getTokenPrecedence() const;

public:
    Parser(const std::string &filename);
    void parse();
};

}

#endif
