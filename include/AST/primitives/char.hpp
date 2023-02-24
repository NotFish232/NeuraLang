#ifndef CHAR_HPP
#define CHAR_HPP

#include "../node.hpp"

namespace nl {

class CharAST : public NodeAST {
private:
    std::string m_value;
    size_t m_numBits;

    const static size_t default_num_bits;

public:
    CharAST(const std::string &value, size_t numBits = default_num_bits);
    ~CharAST();
    const std::string &get_value() const;
    llvm::Value *make_IR() const override;
};

}

#endif