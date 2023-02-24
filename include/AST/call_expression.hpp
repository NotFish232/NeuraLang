//
// Created by piuslee on 2/18/23.
//

#ifndef CALLEXPRAST_HPP
#define CALLEXPRAST_HPP

#include "node.hpp"
#include "variable.hpp"

namespace nl {

// function calls syntax tree
class CallExpressionAST : public NodeAST {
    std::string m_funcName;
    std::vector<NodeAST> m_args;

public:
    CallExpressionAST(const std::string &funcName, const std::vector<NodeAST> &args);
    ~CallExpressionAST();
    const std::string &get_func_name() const;
    const std::vector<NodeAST> &get_args() const;
    llvm::Value *make_IR() const override;
};

}

#endif
