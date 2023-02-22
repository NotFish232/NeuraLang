#ifndef STRING_HPP
#define STRING_HPP

#include "base.hpp"

namespace nl {

class StringAST : Base {
private:
    std::string m_str;

public:
    StringAST(const std::string &str);
    ~StringAST();
    const std::string &get_str() const;
    llvm::Value *make_IR() override;
};

}

#endif