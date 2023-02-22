#ifndef TYPE_HPP
#define TYPE_HPP

#include <llvm/IR/IRBuilder.h>

#include "../neuralang.hpp"

namespace nl {

/**
 * @param typeStr type that was passed by lexer
 * @param n makes type into an array, where n is the number of elements
 * @note if you want a string, pass typeStr = 'char' and n = num of chars
 * @return llvm type that can be used for building IR
*/

llvm::Type *get_type_from_str(const std::string &typeStr, int n = -1);

}

#endif