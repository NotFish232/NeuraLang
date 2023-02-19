#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstdlib>
#include <string>

extern int curTok;

int getToken();
int getNextToken();

extern std::string identifierStr;
extern double numerical;

#endif