//
// Created by piuslee on 2/18/23.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#define DEBUG 1

#include <iostream>

class Logger {
public:
    static void error(const std::string &str);
};

#endif
