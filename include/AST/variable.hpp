#ifndef VARIABLEAST_HPP
#define VARIABLEAST_HPP

#include <map>

#include "node.hpp"

// syntax tree for variables
namespace nl {

class VariableAST : public NodeAST {
    std::string m_name;
    llvm::Type *m_type;

public:
    VariableAST(const std::string &name, llvm::Type *type);
    ~VariableAST();
    const std::string &get_name() const;
    llvm::Type *get_type() const;
    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif