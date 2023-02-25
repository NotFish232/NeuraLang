#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <set>
#include <string>
#include <map>

namespace nl {

extern const std::set<std::string> keywords;
extern const std::set<std::string> valid_long_symbols;
extern const std::set<std::string> core_types;
extern const std::map<std::string, int> binary_operator_precedence;

}

#endif