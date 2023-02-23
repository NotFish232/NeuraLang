
#ifndef FUNCTIONSIGNATUREAST_HPP
#define FUNCTIONSIGNATUREAST_HPP

#include "node_ast.hpp"
#include "variable.hpp"

namespace nl {

class FunctionSignatureAST : NodeAST {
    std::string m_name;
    std::vector<VariableAST> m_args;
    llvm::Type *m_returnType;

public:
    FunctionSignatureAST(const std::string &name,
                         const std::vector<VariableAST> &args,
                         const std::string &returnTypeStr);

    const std::string &get_name() const;
    const std::vector<VariableAST> &get_args() const;
    const llvm::Type *const &get_return_type() const;
    llvm::Function *make_IR() override;
};

}

#endif
