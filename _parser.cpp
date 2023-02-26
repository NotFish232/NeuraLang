//
// Created by piuslee on 2/18/23.
//

#include "../include/parser.hpp"

using namespace std;
using namespace llvm;

// for binary operations
std::map<char, int> binopPrecedence = {
    { '<', 10 },
    { '+', 20 },
    { '-', 20 },
    { '*', 40 }
};

Parser::Parser(const string& filename)
{
    m_fileHandler = ifstream(filename, ios::in);
    m_lexer.set_stream(m_fileHandler);
}

void Parser::parse()
{
    m_lexer.get_next_token();
    while (m_lexer.get_curr_token().type != TokenType::_eof) {
        switch (m_lexer.get_curr_token().type) {
        case TokenType::_def:
            handleDefinition();
            break;
        case TokenType::_extern:
            handleExtern();
            break;
        default:
            handleTopLevelExpression();
            break;
        }
    }
}

// begin tree parsing
unique_ptr<ExprAST> Parser::parsePrimary()
{
    Token currentToken = m_lexer.get_curr_token();
    switch (currentToken.type) {
    case TokenType::_identifier:
        return parseIdentifierExpr();
    case TokenType::_number:
        return parseNumberExpr();
    case TokenType::_string:
        return parseStringExpr();
    case TokenType::_leftParen:
        return parseParenExpr();
    case TokenType::_if:
        return parseIfExpr();
    default:
        cerr << "LogError: unknown token: " << currentToken.type << '\n';
        return nullptr;
    }
}

// parenth parse
unique_ptr<ExprAST> Parser::parseParenExpr()
{
    // set next token in buffer
    m_lexer.get_next_token();

    auto expression = parseExpression();

    if (!expression) {
        return nullptr;
    }

    if (m_lexer.get_curr_token().type != TokenType::_rightParen) {
        logger.error("expected )");
        return nullptr;
    }

    m_lexer.get_next_token(); // eat

    return expression;
}

// expressions
unique_ptr<ExprAST> Parser::parseIdentifierExpr()
{
    string id = m_lexer.get_curr_token().identifier;
    m_lexer.get_next_token(); // eat

    if (m_lexer.get_curr_token().identifier != "(")
        return std::make_unique<VariableExprAST>(id);

    // handle arguments
    m_lexer.get_next_token(); // eat
    vector<unique_ptr<ExprAST>> args;
    if (m_lexer.get_curr_token().identifier != ")") {
        // i am so sorry
        while (true) {
            if (auto arg = parseExpression()) {
                args.push_back(std::move(arg));
            } else {
                return nullptr;
            }

            if (m_lexer.get_curr_token().identifier == ")")
                break;
            if (m_lexer.get_curr_token().identifier != ",") {
                logger.error("expected ) to end args or , to get new args");
                return nullptr;
            }

            m_lexer.get_next_token(); // eat
        }
    }
    m_lexer.get_next_token(); // eat

    return make_unique<CallExprAST>(id, std::move(args));
}

// parse number
unique_ptr<ExprAST> Parser::parseNumberExpr()
{
    auto Result = make_unique<NumericExprAST>(m_lexer.get_curr_token().numVal);
    m_lexer.get_next_token();
    return std::move(Result);
}

unique_ptr<ExprAST> Parser::parseStringExpr()
{
    auto result = make_unique<StringExprAST>(m_lexer.get_curr_token().identifier);
    m_lexer.get_next_token();
    return std::move(result);
}

int Parser::getTokenPrecedence() const
{
    Token curTok = m_lexer.get_curr_token();
    if (!isascii(curTok.identifier[0])) {
        return -1;
    }

    int TokPrec = binopPrecedence[curTok.identifier[0]];
    if (TokPrec <= 0)
        return -1;

    return TokPrec;
}

// parse binary operations
unique_ptr<ExprAST> Parser::parseBinaryOperationRHS(int expressionPrecedence, unique_ptr<ExprAST> LHS)
{
    // sorry again
    while (true) {
        int tokenPrecedence = getTokenPrecedence();
        if (tokenPrecedence < expressionPrecedence) {
            return LHS;
        }

        Token binaryOperation = m_lexer.get_curr_token();
        m_lexer.get_next_token(); // eat

        auto RHS = parsePrimary();
        if (!RHS) {
            return nullptr;
        }

        int nextPrecedence = getTokenPrecedence();
        if (tokenPrecedence < nextPrecedence) {
            RHS = parseBinaryOperationRHS(++tokenPrecedence, std::move(RHS));
            if (!RHS) {
                return nullptr;
            }
        }

        // merge the operation from the left hand side and the right hand side
        LHS = std::make_unique<BinaryExprAST>(binaryOperation.identifier[0], std::move(LHS), std::move(RHS));
    }
}

// expression parsing
unique_ptr<ExprAST> Parser::parseExpression()
{
    auto LHS = parsePrimary();
    if (!LHS)
        return nullptr;

    return parseBinaryOperationRHS(0, std::move(LHS));
}

// parse the function sig
unique_ptr<PrototypeAST> Parser::parsePrototype()
{
    logger.note("Reached prototype.");

    // this section grabs the function name
    if (m_lexer.get_curr_token().type != TokenType::_identifier) {
        logger.error("expected function name in prototype");
        return nullptr;
    }

    logger.note("Valid function name.");

    string functionName = m_lexer.get_curr_token().identifier;
    m_lexer.get_next_token(); // eat

    logger.note("Ate function name.");

    // this section is literally the (args, args) part
    if (m_lexer.get_curr_token().type != TokenType::_leftParen) {
        logger.error("expected '(' in prototype");
        return nullptr;
    }

    logger.note("Valid arg begin.");

    std::vector<std::string> argumentNames;
    while (m_lexer.get_next_token().type == TokenType::_identifier) {
        cout << "LOGGED TOKEN: " << m_lexer.get_curr_token().type << '\n';
        argumentNames.push_back(m_lexer.get_curr_token().identifier);
    }

    if (m_lexer.get_curr_token().type != TokenType::_rightParen) {
        logger.error("expected ')' in prototype");
        return nullptr;
    }

    m_lexer.get_next_token(); // eat

    return make_unique<PrototypeAST>(functionName, std::move(argumentNames));
}

unique_ptr<FunctionAST> Parser::parseDefinition()
{
    m_lexer.get_next_token();

    auto prototype = parsePrototype();
    if (!prototype)
        return nullptr; // check if the prototype is valid
    logger.note("Valid Prototype.");

    if (auto expression = parseExpression()) {
        return make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

unique_ptr<FunctionAST> Parser::parseTopLevelExpr()
{
    if (auto expression = parseExpression()) {
        auto prototype = make_unique<PrototypeAST>("__anon_expr", vector<string>());
        return make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

std::unique_ptr<PrototypeAST> Parser::parseExtern()
{
    m_lexer.get_next_token();
    return parsePrototype();
}

std::unique_ptr<IfExprAST> Parser::parseIfExpr()
{
    // eat the if statement
    m_lexer.get_next_token();

    // condition
    auto condition = parseExpression();
    if (!condition) {
        logger.error("invalid (if) condition");
        return nullptr;
    }
    logger.note("reached/passed if");

    if (m_lexer.get_curr_token().type != TokenType::_then) {
        logger.error("expected then statement");
        return nullptr;
    }
    m_lexer.get_next_token();

    auto then = parseExpression();
    if (!condition) {
        logger.error("invalid then condition");
        return nullptr;
    }
    logger.note("reached/passed then");

    if (m_lexer.get_curr_token().type != TokenType::_else) {
        logger.error("expected else statement");
        return nullptr;
    }
    m_lexer.get_next_token(); // eat the else

    auto _else = parseExpression();
    if (!_else) {
        logger.error("invalid else condition");
        return nullptr;
    }

    return std::make_unique<IfExprAST>(std::move(condition), std::move(then), std::move(_else));
}

void Parser::handleDefinition()
{
    logger.note("Reached definition.");
    if (auto FnAST = parseDefinition()) {
        if (auto* FnIR = FnAST->codegen()) {
            fprintf(stderr, "read function definition:");
            FnIR->print(errs());
            fprintf(stderr, "\n");
        }
    } else {
        m_lexer.get_next_token();
    }
}

void Parser::handleExtern()
{
    if (auto ProtoAST = parseExtern()) {
        if (auto* FnIR = ProtoAST->codegen()) {
            fprintf(stderr, "read extern:");
            // FnIR->print(errs());
            fprintf(stderr, "\n");
        }
    } else {
        m_lexer.get_next_token();
    }
}

void Parser::handleTopLevelExpression()
{
    if (auto FnAST = parseTopLevelExpr()) {
        if (auto* FnIR = FnAST->codegen()) {
            fprintf(stderr, "read top-level expression:");
            FnIR->print(errs());
            fprintf(stderr, "\n");

            FnIR->eraseFromParent();
        }
    } else {
        m_lexer.get_next_token();
    }
}