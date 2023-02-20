#ifndef LAYER_HPP
#define LAYER_HPP

#include "node.cpp"
#include <vector>

template <class T>
class Layer {
private:
    std::vector<Node<T>> m_vector;
public:
    std::vector<T> forwardPropogation();
    std::vector<T> backPropogation();
};
#endif