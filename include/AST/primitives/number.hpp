#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

#include "../node_ast.hpp"

namespace nl {

class NumberAST : NodeAST {
private:
    std::string m_value, m_type;

public:
    NumberAST(const std::string &value, const std::string &type);
    ~NumberAST();
    const std::string &get_value() const;
    const std::string &get_type() const;
    llvm::Value *make_IR() override;
};

}

#endif