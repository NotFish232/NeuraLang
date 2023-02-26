//
// Created by piuslee on 2/18/23.
//

#ifndef CALLEXPRAST_HPP
#define CALLEXPRAST_HPP

#include "../node.hpp"
#include "../variables/variable.hpp"

namespace nl {

// function calls syntax tree
class CallExpressionAST : public NodeAST {
    std::string m_func_name;
    std::vector<std::unique_ptr<NodeAST>> m_args;

public:
    CallExpressionAST(const std::string &func_name,
                      std::vector<std::unique_ptr<NodeAST>> &args);
    ~CallExpressionAST();
    const std::string &get_func_name() const;
    const std::vector<std::unique_ptr<NodeAST>> &get_args() const;
    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif
