#ifndef STRING_HPP
#define STRING_HPP

#include "../node.hpp"

namespace nl {

class StringAST : public NodeAST {
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