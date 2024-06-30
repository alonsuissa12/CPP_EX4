//alonsuissa12@gmail.com 211344015
// Created by alon on 6/19/24.
//


#ifndef CPP_EX4_NODE_HPP
#define CPP_EX4_NODE_HPP

#include <vector>
#include <stdexcept>

template<typename T>
class Node {
private:
    int maxChildren; // maxChildren is the maximum number of children the node can have
    int curNumOfChildren; // curNumOfChildren is the current number of children the node has
    T value; // value is the data stored in the node
    std::vector<Node<T> *> children; // children is a vector of pointers to the node's children

public:
    // Constructor initializing value and maxChildren
    Node(T value, int maxChildren) : maxChildren(maxChildren), value(value), curNumOfChildren(0) {}

    // Constructor initializing value with default maxChildren of 2
    explicit Node(T value) : maxChildren(2), value(value), curNumOfChildren(0) {}

    // Destructor to delete all children
    ~Node();

    // Getter for maxChildren
    int getMaxChildren() const;

    // Getter for current number of children
    int getCurNumOfChildren() const { return curNumOfChildren; }

    // Getter for node's value
    T getValue() const;

    // Getter for children
    const std::vector<Node<T>*>& getChildren() const;

    // Adds a child to the node
    void addChild(Node<T>* child);

    // Equality operator to compare nodes
    bool operator==(const Node<T> &other) const;

    // Inequality operator to compare nodes
    bool operator!=(const Node<T> &other) const;
};

// Destructor implementation
template<typename T>
Node<T>::~Node() {
    // Recursively delete all children
    for (Node<T> *child : children) {
        delete child;
    }
}

// Getter for maxChildren
template<typename T>
int Node<T>::getMaxChildren() const {
    return maxChildren;
}

// Getter for node's value
template<typename T>
T Node<T>::getValue() const {
    return value;
}

// Getter for children
template<typename T>
const std::vector<Node<T> *> &Node<T>::getChildren() const {
    return children;
}

// Adds a child to the node
template<typename T>
void Node<T>::addChild(Node<T> *child) {
    if (children.size() < maxChildren) {
        children.push_back(child);
        curNumOfChildren++;
    } else {
        throw std::runtime_error("Maximum number of children exceeded");
    }
}

// Equality operator to compare nodes
template<typename T>
bool Node<T>::operator==(const Node<T> &other) const {
    return value == other.value;
}

// Inequality operator to compare nodes
template<typename T>
bool Node<T>::operator!=(const Node<T> &other) const {
    return !(value == other.value);
}

#endif // CPP_EX4_NODE_HPP