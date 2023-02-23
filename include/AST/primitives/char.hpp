#ifndef CHAR_HPP
#define CHAR_HPP

#include "../node_ast.hpp"

namespace nl {

class Char : NodeAST {
private:
    std::string m_value;
    size_t m_numBits;

    const static size_t default_num_bits;

public:
    Char(const std::string &value, size_t numBits = default_num_bits);
    ~Char();
    const std::string &get_value() const;
    llvm::Value *make_IR() override;
};

}

#endif