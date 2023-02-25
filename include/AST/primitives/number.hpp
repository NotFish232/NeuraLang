#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

#include "../node.hpp"

namespace nl {

class NumberAST : public NodeAST {
private:
    std::string m_value;

public:
    NumberAST(const std::string &value);
    ~NumberAST();
    const std::string &get_value() const;
    llvm::Value *make_IR(ValueMap &scope) const override;
};

}

#endif