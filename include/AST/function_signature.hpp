
#ifndef FUNCTIONSIGNATUREAST_HPP
#define FUNCTIONSIGNATUREAST_HPP

#include "node.hpp"
#include "variable.hpp"

namespace nl {

class FunctionSignatureAST : public NodeAST {
    std::string m_name;
    std::vector<VariableAST> m_args;
    llvm::Type *m_return_type;

public:
    FunctionSignatureAST(const std::string &name,
                         const std::vector<VariableAST> &args,
                         llvm::Type *return_type);

    const std::string &get_name() const;
    const std::vector<VariableAST> &get_args() const;
    const llvm::Type *const &get_return_type() const;
    llvm::Function *make_IR() const override;
};

}

#endif
