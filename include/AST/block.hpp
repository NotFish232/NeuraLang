#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "node.hpp"

namespace nl {

class BlockAST : public NodeAST {
private:
    std::vector<std::unique_ptr<NodeAST>> m_contents;

public:
    BlockAST();
    ~BlockAST();
    void add(std::unique_ptr<NodeAST> expr);
    llvm::Value *make_IR() override;
};

};
#endif