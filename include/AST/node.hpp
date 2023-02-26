#ifndef NODE_HPP
#define NODE_HPP

#include <llvm/IR/IRBuilder.h>

#include "../neuralang.hpp"
#include <map>

using ValueMap = std::map<std::string, llvm::Value *>;
namespace nl {

// base class for all
class NodeAST {
public:
    virtual ~NodeAST();
    virtual llvm::Value *make_IR(ValueMap &scope) const;
};

}

#endif
