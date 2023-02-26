#ifndef NODE_HPP
#define NODE_HPP

#include <llvm/IR/IRBuilder.h>
#include <map>

#include "../neuralang.hpp"

namespace nl {

using ValueMap = std::map<std::string, llvm::Value *>;

// base class for all
class NodeAST {
public:
    // a null value that can be returned from functions that require a &, same thing as in token
    static std::unique_ptr<NodeAST> null;

    virtual ~NodeAST();
    virtual llvm::Value *make_IR(ValueMap &scope) const;
};

}

#endif
