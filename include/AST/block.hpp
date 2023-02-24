#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "node.hpp"

namespace nl {

class BlockAST : public NodeAST {
private:
    std::vector<NodeAST> m_contents;

public:
    BlockAST();
    ~BlockAST();
    void add(NodeAST expr);
    llvm::Value *make_IR() const override;
};

};
#endif