//
// Created by piuslee on 2/18/23.
//

#include "../include/parser.hpp"

using namespace std;

//for binary operations
std::map<char, int> binopPrecedence;

//begin tree parsing
unique_ptr<ExprAST> parsePrimary() {
    switch (curTok) {
        default:
            logger.error("unknown token");
            return nullptr;
        case tok_identifier:
            return parseIdentifierExpr();
        case tok_number:
            return parseNumberExpr();
        case '(':
            return parseParenExpr();
    }
}

//parenth parse
unique_ptr<ExprAST> parseParenExpr() {
    //set next token in buffer
    getNextToken();

    auto V = parseExpression();
    if(!V) return nullptr;

    if(curTok != ')') {
        logger.error("expected )");
        return nullptr;
    }

    getNextToken(); //eat
    return V;
}

//expressions
unique_ptr<ExprAST> parseIdentifierExpr() {
    string id = identifierStr;
    getNextToken(); //eat

    if(curTok != '(') return std::make_unique<VariableExprAST>(id);

    //handle arguments
    getNextToken(); //eat
    vector<unique_ptr<ExprAST>> args;
    if(curTok != ')') {
        //i am so sorry
        while(true) {
            if(auto arg = parseExpression()) args.push_back(std::move(arg));
            else return nullptr;

            if(curTok == ')') break;
            if(curTok != ',') {
                logger.error("expected ) to end args or , to get new args");
                return nullptr;
            }

            getNextToken(); //eat
        }
    }
    getNextToken(); //eat

    return make_unique<CallExprAST>(id, std::move(args));
}

// order of precedence
static int getTokenPrecedence(){
    if(!isascii(curTok)) return -1;

    int tokPrecedence = binopPrecedence[curTok];
    if(tokPrecedence <= 0) return -1;

    return tokPrecedence;
}

//parse number
unique_ptr<ExprAST> parseNumberExpr() {
    auto Result = make_unique<NumberExprAST>(numerical);
    getNextToken();
    return std::move(Result);
}

//parse binary operations
unique_ptr<ExprAST> parseBinaryOperationRHS(int expressionPrecedence, unique_ptr<ExprAST> LHS) {
    //sorry again
    while(true) {
        int tokenPrecedence = getTokenPrecedence();
        if(tokenPrecedence < expressionPrecedence) return LHS;

        int binaryOperation = curTok;
        getNextToken(); //eat

        auto RHS = parsePrimary();
        if(!RHS) return nullptr;

        int nextPrecedence = getTokenPrecedence();
        if(tokenPrecedence < nextPrecedence) {
            RHS = parseBinaryOperationRHS(++tokenPrecedence, std::move(RHS));
            if(!RHS) return nullptr;
        }

        //merge the operation from the left hand side and the right hand side
        LHS = make_unique<BinaryExprAST>(binaryOperation, std::move(LHS), std::move(RHS));
    }
}

//expression parsing
unique_ptr<ExprAST> parseExpression() {
    auto LHS = parsePrimary();
    if(!LHS) return nullptr;

    return parseBinaryOperationRHS(0, std::move(LHS));
}

//parse the function sig
unique_ptr<PrototypeAST> parsePrototype() {
    //this section grabs the function name
    if(tok_identifier != curTok) {
        logger.error("expected function name in prototype");
        return nullptr;
    }

    string functionName = identifierStr;
    getNextToken(); //eat

    //this section is literally the (args, args) part
    if(curTok != '(') {
        logger.error("expected '(' in prototype");
        return nullptr;
    }

    std::vector<std::string> argumentNames;
    while (getNextToken() == tok_identifier) {
        argumentNames.push_back(identifierStr);
    }

    if(curTok != ')') {
        logger.error("expected ')' in prototype");
        return nullptr;
    }

    getNextToken(); //eat

    return make_unique<PrototypeAST>(functionName, std::move(argumentNames));
}

unique_ptr<FunctionAST> parseDefinition() {
    getNextToken();

    auto prototype = parsePrototype();
    if(!prototype) return nullptr; //check if the prototype is valid

    if(auto expression = parseExpression()) {
        return make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

unique_ptr<FunctionAST> parseTopLevelExpr() {
    if(auto expression = parseExpression()) {
        auto prototype = make_unique<PrototypeAST>("__anon_expr", vector<string>());
        return make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

std::unique_ptr<PrototypeAST> parseExtern() {
    getNextToken();
    return parsePrototype();
}