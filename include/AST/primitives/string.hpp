#ifndef STRING_HPP
#define STRING_HPP

#include "../node_ast.hpp"

namespace nl {

class StringAST : NodeAST {
private:
    std::string m_value;

public:
    StringAST(const std::string &value);
    ~StringAST();
    const std::string &get_value() const;
    llvm::Value *make_IR() override;
};

}

#endif