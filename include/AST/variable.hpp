#ifndef VARIABLERAST_HPP
#define VARIABLEAST_HPP

#include <map>

#include "node.hpp"
#include "type.hpp"

// syntax tree for variables
namespace nl {

class VariableAST : public NodeAST {
    std::string m_name;
    llvm::Type *m_type;
    std::set<std::string> scope;

public:
    VariableAST(const std::string &name, const std::string &typeStr);
    ~VariableAST();
    const std::string &get_name() const;
    const llvm::Type *const &get_type() const;
    llvm::Value *make_IR() override;
};

}

#endif