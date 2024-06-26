//
// Created by alon on 6/19/24.
//
//alonsuissa12@gmail.com 211344015

#ifndef CPP_EX4_NODE_HPP
#define CPP_EX4_NODE_HPP
#include <vector>
#include <stdexcept>

template<typename T>
class Node {
private:
    int maxChildren; // maxChildren is the maximum number of children the node can have
    int curNumOfChildren;
    T value;
    std::vector<Node<T> *> children;
public:
    Node(int maxChildren, T value) : maxChildren(maxChildren), value(value),curNumOfChildren(0) {}
    explicit Node(T value):maxChildren(2),value(value),curNumOfChildren(0){};
    ~Node();

    int getMaxChildren() const;

    int getCurNumOfChildren(){return curNumOfChildren;}

    T getValue() const;

    const std::vector<Node<T>*>& getChildren() const;

    void addChild(Node<T>* child) ;
};

template<typename T>
Node<T>::~Node() {
    // Recursively delete all children
    for (Node<T> *child: children) {
        delete child;
    }
}

template<typename T>
// Additional member functions can be added here
int Node<T>::getMaxChildren() const {
    return maxChildren;
}

template<typename T>
T Node<T>::getValue() const {
    return value;
}

template<typename T>
const std::vector<Node<T> *> &Node<T>::getChildren() const {
    return children;
}

template<typename T>
void Node<T>::addChild(Node<T> *child) {
    if (children.size() < maxChildren) {
        children.push_back(child);
        curNumOfChildren++;
    } else {
        throw std::runtime_error("Maximum number of children exceeded");
    }
}

#endif //CPP_EX4_NODE_HPP
