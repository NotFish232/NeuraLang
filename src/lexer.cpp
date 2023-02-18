#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


const string functionDefinition = "def";
const string externDefinition = "extern";


enum class Token {
    _eof,

    // commands
    _def,
    _extern,

    // primary
    _identifier,
    _number
};

static string identifierStr;
static double numVal;

// gets one token from stream, mutates stream
static Token getToken(istream &stream) {
    char lastChar = ' ';

    while (isspace(lastChar)) {
        stream.get(lastChar);
    }

    if (isalpha(lastChar)) {
        string identifier = "";
        do {
            identifier += lastChar;
        } while (stream.get(lastChar) && isalnum(lastChar));

        if (identifier == functionDefinition) {
            return Token::_def;
        }
        if (identifier == externDefinition) {
            return Token::_extern;
        }
    }

    if (isdigit(lastChar)) {
        string num = "";

        do {
            num += lastChar;
        } while (stream.get(lastChar) && isalnum(lastChar));

        numVal = stoi(num);

        return Token::_number;
    }

    if (lastChar == '#') {
        do {
            stream.get(lastChar);
        } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if (!lastChar != EOF) return getToken(stream);
    }   

    if (lastChar == EOF) return Token::_eof;


    return lastChar;

}

int main(int argc, char **argv) {
    if (argc == 1) {
        return EXIT_FAILURE;
    }
    string filename = argv[1];

    string code;
}