//
// Created by piuslee on 2/18/23.
//

#include "../include/parser.hpp"

using namespace std;
using namespace nl;
using namespace llvm;

// for binary operations
std::map<char, int> binopPrecedence = {
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40}};

Parser::Parser(const string &filename) {
    m_fileHandler = ifstream(filename, ios::in);
    m_lexer.setStream(m_fileHandler);
}

void Parser::parse() {
    while (m_lexer.getCurrentToken().type != TokenType::_eof) {
        switch (m_lexer.getCurrentToken().type) {
        case TokenType::_def:
            parseDefinition();
            break;
        case TokenType::_extern:
            parseExtern();
            break;
        default:
            parseTopLevelExpr();
            break;
        }
    }
}

// begin tree parsing
unique_ptr<ExprAST> Parser::parsePrimary() {
    Token currentToken = m_lexer.getCurrentToken();
    switch (currentToken.type) {
    case TokenType::_identifier:
        return parseIdentifierExpr();
    case TokenType::_number:
        return parseNumberExpr();
    case TokenType::_leftParen:
        return parseParenExpr();
    default:
        logger.error("unknown token");
        return nullptr;
    }
}

// parenth parse
unique_ptr<ExprAST> Parser::parseParenExpr() {
    // set next token in buffer
    m_lexer.getNextToken();

    auto V = parseExpression();
    if (!V)
        return nullptr;

    if (m_lexer.getCurrentToken().type != TokenType::_rightParen) {
        logger.error("expected )");
        return nullptr;
    }

    m_lexer.getNextToken(); // eat
    return V;
}

// expressions
unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    string id = m_lexer.getCurrentToken().identifier;
    m_lexer.getNextToken(); // eat

    if (m_lexer.getCurrentToken().identifier != "(")
        return std::make_unique<VariableExprAST>(id);

    // handle arguments
    m_lexer.getNextToken(); // eat
    vector<unique_ptr<ExprAST>> args;
    if (m_lexer.getCurrentToken().identifier != ")") {
        // i am so sorry
        while (true) {
            if (auto arg = parseExpression()) {
                args.push_back(std::move(arg));
            } else {
                return nullptr;
            }

            if (m_lexer.getCurrentToken().identifier == ")")
                break;
            if (m_lexer.getCurrentToken().identifier != ",") {
                logger.error("expected ) to end args or , to get new args");
                return nullptr;
            }

            m_lexer.getNextToken(); // eat
        }
    }
    m_lexer.getNextToken(); // eat

    return make_unique<CallExprAST>(id, std::move(args));
}

// parse number
unique_ptr<ExprAST> Parser::parseNumberExpr() {
    auto Result = make_unique<NumberExprAST>(m_lexer.getCurrentToken().numVal);
    m_lexer.getNextToken();
    return std::move(Result);
}

// parse binary operations
unique_ptr<ExprAST> Parser::parseBinaryOperationRHS(int expressionPrecedence, unique_ptr<ExprAST> LHS) {
    // sorry again
    while (true) {
        int tokenPrecedence = binopPrecedence[expressionPrecedence];
        if (tokenPrecedence < expressionPrecedence)
            return LHS;

        Token binaryOperation = m_lexer.getCurrentToken();
        m_lexer.getNextToken(); // eat

        auto RHS = parsePrimary();
        if (!RHS)
            return nullptr;

        int nextPrecedence = binopPrecedence[expressionPrecedence];
        if (tokenPrecedence < nextPrecedence) {
            RHS = parseBinaryOperationRHS(++tokenPrecedence, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        // merge the operation from the left hand side and the right hand side
        LHS = make_unique<BinaryExprAST>(binaryOperation, std::move(LHS), std::move(RHS));
    }
}

// expression parsing
unique_ptr<ExprAST> Parser::parseExpression() {
    auto LHS = parsePrimary();
    if (!LHS)
        return nullptr;

    return parseBinaryOperationRHS(0, std::move(LHS));
}

// parse the function sig
unique_ptr<PrototypeAST> Parser::parsePrototype() {
    // this section grabs the function name
    if (m_lexer.getCurrentToken().type != TokenType::_identifier) {
        logger.error("expected function name in prototype");
        return nullptr;
    }

    string functionName = m_lexer.getCurrentToken().identifier;
    m_lexer.getNextToken(); // eat

    // this section is literally the (args, args) part
    if (m_lexer.getCurrentToken().identifier != "(") {
        logger.error("expected '(' in prototype");
        return nullptr;
    }

    std::vector<std::string> argumentNames;
    while (m_lexer.getNextToken().type != TokenType::_identifier) {
        argumentNames.push_back(m_lexer.getCurrentToken().identifier);
    }

    if (m_lexer.getCurrentToken().identifier != ")") {
        logger.error("expected ')' in prototype");
        return nullptr;
    }

    m_lexer.getNextToken(); // eat

    return make_unique<PrototypeAST>(functionName, std::move(argumentNames));
}

unique_ptr<FunctionAST> Parser::parseDefinition() {
    m_lexer.getNextToken();

    auto prototype = parsePrototype();
    if (!prototype)
        return nullptr; // check if the prototype is valid

    if (auto expression = parseExpression()) {
        return make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

unique_ptr<FunctionAST> Parser::parseTopLevelExpr() {
    if (auto expression = parseExpression()) {
        auto prototype = make_unique<PrototypeAST>("__anon_expr", vector<string>());
        return make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

std::unique_ptr<PrototypeAST> Parser::parseExtern() {
    m_lexer.getNextToken();
    return parsePrototype();
}