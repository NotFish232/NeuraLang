#include "../include/lexer.hpp"
#include "../include/token.h"

using namespace std;

int curTok;
string identifierStr;
double numerical;

int getToken() {
    static int lastChar = ' ';
    while(isspace(lastChar)) lastChar = getchar();

    //identifier & keyword handling
    if(isalpha(lastChar)) {
        identifierStr = lastChar;
        while(isalnum(lastChar = getchar())) identifierStr += lastChar;

        if(identifierStr == "def") return tok_def;
        if(identifierStr == "extern") return tok_extern;
        return tok_identifier;
    }

    //number handling
    if(isdigit(lastChar) || lastChar == '.') {
        //eat all number-qualifying chars
        string buffer;
        do {
            buffer += lastChar;
            lastChar = getchar();
        } while (isdigit(lastChar) || lastChar == '.');

        //convert string to number
        numerical = strtod(buffer.c_str(), 0);

        return tok_number;
    }

    //comment handling
    if(lastChar == '#') {
        do lastChar = getchar();
        while (lastChar != EOF && lastChar != '\n' && lastChar != '\r'); //i hate windows users

        if(lastChar == EOF) {
            return ::getToken();
        }
    }

    //exceptional handling
    if(lastChar == EOF) return tok_eof;

    int temp = lastChar;
    lastChar = getchar(); //eat
    return temp;
}

int getNextToken() {
    return curTok = ::getToken();
}