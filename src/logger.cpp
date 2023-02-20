//
// Created by piuslee on 2/18/23.
//

#include "../include/logger.hpp"

using namespace std;

void Logger::error(const string &str) {
#ifdef DEBUG
    cerr << "LogError: " << str << '\n';
#endif
}

void Logger::note(const string &str) {
#ifdef DEBUG
    cout << "NOTE: " << str << '\n';
#endif
}