//
// Created by alon on 6/18/24.
//
//alonsuissa12@gmail.com 211344015

#ifndef CPP_EX4_TREE_HPP
#define CPP_EX4_TREE_HPP

#define LEFT_CHILD 0
#define RIGHT_CHILD 1

#include <wx/wx.h>
#include <wx/dc.h>
#include <wx/string.h>
#include <wx/dcbuffer.h>
#include <vector>
#include <stdexcept>
#include <stack>
#include <queue>
#include <functional>
#include "Node.hpp"
#include <iostream>
#include <sstream>


// todo: take care of const iterators
// todo: add heap iterator

template<typename T>
class Tree {
private:
    Node<T> *root;
    int maxChildren;
private:
    void drawNode(wxDC &dc, Node<T> *node, int x, int y, int width, int height);
public:
    explicit Tree(T rootValue, int maxChildren);


    explicit Tree(int maxChildren);

    explicit Tree();

    ~Tree();

    int getMaxChildren() const {
        return maxChildren;
    }


    int add_root(Node<T> *);

    Node<T> *getRoot() const;

    int add_sub_node(Node<T> *dad, Node<T> *child);

    void drawTree(wxDC &dc, int x, int y, int width, int height);


//the iterator inside the tree class because it's designed for it.
    class MyIterator {
    public:

        virtual bool hasNext() const = 0;

        virtual T next() = 0;
    };

// Iterator class for DFS
    class DfsIterator : public MyIterator {
    private:
        std::stack<Node<T> *> nodeStack;
    public:
        explicit DfsIterator(Node<T> *root) {
            if (root) {
                nodeStack.push(root);
            }
        }

        bool hasNext() const override {
            return !nodeStack.empty();
        }

        T next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }

            Node<T> *currentNode = nodeStack.top();
            nodeStack.pop();

            for (auto child: currentNode->getChildren()) {
                nodeStack.push(child);
            }

            return currentNode->getValue();
        }

        bool operator==(const DfsIterator &other) const {
            if (nodeStack.empty() && other.nodeStack.empty()) {
                return true;
            }
            if (nodeStack.empty() || other.nodeStack.empty()) {
                return false;
            }
            return nodeStack.top() == other.nodeStack.top();
        }

        bool operator!=(const DfsIterator &other) const {
            return !(*this == other);
        }

        Node<T> *operator*() {
            return this->nodeStack.top();
        }

        DfsIterator operator++() {
            next();
            return *this;
        }

        DfsIterator operator++(int) {
            DfsIterator temp = *this; // Save the current state
            next(); // Increment the iterator
            return temp; // Return the saved state
        }
    };

    class PreOrderIterator : public MyIterator {
    private:
        std::stack<Node<T> *> nodeStack;
        int maxChildNum;
    public:
        explicit PreOrderIterator(Node<T> *root, int maxChild) {
            if (root)
                nodeStack.push(root);
            maxChildNum = maxChild;
        }

        bool hasNext() const override {
            return !nodeStack.empty();
        }

        T next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }

            Node<T> *currentNode = nodeStack.top();
            nodeStack.pop();
            auto children = currentNode->getChildren();
            if (maxChildNum == 2) {
                if (currentNode->getCurNumOfChildren() == 2)
                    nodeStack.push(children[RIGHT_CHILD]);
                if (currentNode->getCurNumOfChildren() >= 1)
                    nodeStack.push(children[LEFT_CHILD]);

            } else { // dfs like iterator
                for (auto child: children) {
                    nodeStack.push(child);
                }
            }
            return currentNode->getValue();
        }

        bool operator==(const PreOrderIterator &other) const {
            if (!hasNext() && !other.hasNext()) {
                return true;
            }
            if (!hasNext() || !other.hasNext()) {
                return false;
            }
            return nodeStack.top() == other.nodeStack.top();
        }

        bool operator!=(const PreOrderIterator &other) const {
            return !(*this == other);
        }

        Node<T> *operator*() {
            return this->nodeStack.top();
        }

        PreOrderIterator operator++() {
            next();
            return *this;
        }

        PreOrderIterator operator++(int) {
            PreOrderIterator temp = *this; // Save the current state
            next(); // Increment the iterator
            return temp; // Return the saved state
        }

    };

    class PostOrderIterator : public MyIterator {
    private:
        std::stack<Node<T> *> nodeStack;
        int maxChildNum;
    public:
        explicit PostOrderIterator(Node<T> *root, int maxChild) {
            maxChildNum = maxChild;
            if (root) {
                if (maxChildNum == 2) {
                    std::stack<Node<T> *> tempStack;
                    Node<T> *cur = root;
                    while (cur != nullptr) {

                        if (cur->getCurNumOfChildren() >= 1) {
                            tempStack.push(cur->getChildren()[LEFT_CHILD]);
                        }
                        if (cur->getCurNumOfChildren() >= 2)
                            tempStack.push(cur->getChildren()[RIGHT_CHILD]);
                        nodeStack.push(cur);
                        if (tempStack.empty())
                            cur = nullptr;
                        else {
                            cur = tempStack.top();
                            tempStack.pop();
                        }
                    }
                } else {
                    nodeStack.push(root);
                }
            }
        }

        bool hasNext() const override {
            return !nodeStack.empty();
        }

        T next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }

            Node<T> *currentNode = nodeStack.top();
            nodeStack.pop();
            if (maxChildNum == 2) {
                return currentNode->getValue();
            } else { // dfs like iterator
                auto children = currentNode->getChildren();
                for (auto child: children) {
                    nodeStack.push(child);
                }
            }
            return currentNode->getValue();
        }

        bool operator==(const PostOrderIterator &other) const {
            if (nodeStack.empty() && other.nodeStack.empty()) {
                return true;
            }
            if (nodeStack.empty() || other.nodeStack.empty()) {
                return false;
            }
            return nodeStack.top() == other.nodeStack.top();
        }

        bool operator!=(const PostOrderIterator &other) const {
            return !(*this == other);
        }

        Node<T> *operator*() {
            return this->nodeStack.top();
        }

        PostOrderIterator operator++() {
            next();
            return *this;
        }

        PostOrderIterator operator++(int) {
            PostOrderIterator temp = *this; // Save the current state
            next(); // Increment the iterator
            return temp; // Return the saved state
        }

    };

    class InOrderIterator : public MyIterator {
    private:
        std::stack<Node<T> *> nodeStack;
        int maxChildNum;
    private:
        void stackBuild(Node<T> *cur) {
            if (cur->getCurNumOfChildren() == 0)
                nodeStack.push(cur);
            if (cur->getCurNumOfChildren() == 1) {
                nodeStack.push(cur);
                stackBuild(cur->getChildren()[LEFT_CHILD]);
            }
            if (cur->getCurNumOfChildren() == 2) {
                stackBuild(cur->getChildren()[RIGHT_CHILD]);
                nodeStack.push(cur);
                stackBuild(cur->getChildren()[LEFT_CHILD]);
            }
        }

    public:
        explicit InOrderIterator(Node<T> *root, int maxChild) {
            maxChildNum = maxChild;
            if (root) {
                if (maxChildNum == 2) {
                    stackBuild(root);
                } else {
                    nodeStack.push(root);
                }
            }
        }

        bool hasNext() const override {
            return !nodeStack.empty();
        }

        T next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }

            Node<T> *currentNode = nodeStack.top();
            nodeStack.pop();
            if (maxChildNum == 2) {
                return currentNode -> getValue();
            } else { // dfs like iterator
                auto children = currentNode->getChildren();
                for (auto child: children) {
                    nodeStack.push(child);
                }
            }
            return currentNode->getValue();
        }

        bool operator==(const InOrderIterator &other) const {
            if (nodeStack.empty() && other.nodeStack.empty()) {
                return true;
            }
            if (nodeStack.empty() || other.nodeStack.empty()) {
                return false;
            }
            return nodeStack.top() == other.nodeStack.top();
        }

        bool operator!=(const InOrderIterator &other) const {
            return !(*this == other);
        }

        Node<T> *operator*() {
            return this->nodeStack.top();
        }

        InOrderIterator operator++() {
            next();
            return *this;
        }

        InOrderIterator operator++(int) {
            InOrderIterator temp = *this; // Save the current state
            next(); // Increment the iterator
            return temp; // Return the saved state
        }

    };

    class BfsOrderIterator : public MyIterator {
    private:
        std::queue<Node<T> *> nodeQueue;
    public:
        explicit BfsOrderIterator(Node<T> *root) {
            if (root) {
                nodeQueue.push(root);
            }
        }

        bool hasNext() const override {
            return !nodeQueue.empty();
        }

        T next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }
            Node<T> *cur = nodeQueue.front();
            nodeQueue.pop();
            for (int i = 0; i < cur->getCurNumOfChildren(); i++) {
                nodeQueue.push(cur->getChildren()[i]);
            }
            return cur->getValue();
        }

        bool operator==(const BfsOrderIterator &other) const {
            if (nodeQueue.empty() && other.nodeQueue.empty()) {
                return true;
            }
            if (nodeQueue.empty() || other.nodeQueue.empty()) {
                return false;
            }
            return nodeQueue.front() == nodeQueue.front();
        }

        bool operator!=(const BfsOrderIterator &other) const {
            return !(*this == other);
        }

        Node<T> *operator*() {
            return this->nodeQueue.front();
        }

        BfsOrderIterator operator++() {
            next();
            return *this;
        }

        BfsOrderIterator operator++(int) {
            BfsOrderIterator temp = *this; // Save the current state
            next(); // Increment the iterator
            return temp; // Return the saved state
        }

    };

    class MinHeapIterator : public MyIterator {
    private:

        std::priority_queue<T, std::vector<T>, std::greater<T>> heap;
    public:
        explicit MinHeapIterator(Node<T> *root) {
            if (root) {
                std::stack<Node<T>*> stack;
                stack.push(root);
                while (!stack.empty()){
                    Node<T> * cur = stack.top();
                    stack.pop();
                    heap.push(cur->getValue());
                    for(auto child: cur->getChildren() ){
                        stack.push(child);
                    }
                }
            }
        }

        bool hasNext() const override {
            return !heap.empty();
        }

        T next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }
            T cur = heap.top();
            heap.pop();
            return cur;
        }

        bool operator==(MinHeapIterator &other) const {
            if (heap.empty() && other.heap.empty()) {
                return true;
            }
            if (heap.empty() || other.heap.empty()) {
                return false;
            }
            return heap.top() == heap.top();
        }

        bool operator!=( MinHeapIterator &other) const {
            return !(*this == other);
        }

        T operator*() {
            return this->heap.top();
        }

        MinHeapIterator operator++() {
            next();
            return *this;
        }

        MinHeapIterator operator++(int) {
            MinHeapIterator temp = *this; // Save the current state
            next(); // Increment the iterator
            return temp; // Return the saved state
        }

    };

    std::pair<MinHeapIterator, MinHeapIterator> myHeap() {
        return {MinHeapIterator(root), MinHeapIterator(nullptr)};
    }

    std::pair<MinHeapIterator, MinHeapIterator> myHeap() const {
        return {MinHeapIterator(root), MinHeapIterator(nullptr)};
    }

    DfsIterator begin_dfs_scan() { return DfsIterator(root); }

    DfsIterator begin_dfs_scan() const { return DfsIterator(root); }

    DfsIterator end_dfs_scan() { return DfsIterator(nullptr); }

    DfsIterator end_dfs_scan() const { return DfsIterator(nullptr); }


    PreOrderIterator begin_pre_order() { return PreOrderIterator(root, maxChildren); }

    PreOrderIterator begin_pre_order() const { return PreOrderIterator(root, maxChildren); }

    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr, maxChildren); }

    PreOrderIterator end_pre_order() const { return PreOrderIterator(nullptr, maxChildren); }


    PostOrderIterator begin_post_order() { return PostOrderIterator(root, maxChildren); }

    PostOrderIterator begin_post_order() const { return PostOrderIterator(root, maxChildren); }

    PostOrderIterator end_post_order() { return PostOrderIterator(nullptr, maxChildren); }

    PostOrderIterator end_post_order() const { return PostOrderIterator(nullptr, maxChildren); }


    InOrderIterator begin_in_order() { return InOrderIterator(root, maxChildren); }

    InOrderIterator begin_in_order() const { return InOrderIterator(root, maxChildren); }

    InOrderIterator end_in_order() { return InOrderIterator(nullptr, maxChildren); }

    InOrderIterator end_in_order() const { return InOrderIterator(nullptr, maxChildren); }


    BfsOrderIterator begin_bfs_scan() { return BfsOrderIterator(root); }

    BfsOrderIterator begin_bfs_scan() const { return BfsOrderIterator(root); }

    BfsOrderIterator end_bfs_scan() { return BfsOrderIterator(nullptr); }

    BfsOrderIterator end_bfs_scan() const { return BfsOrderIterator(nullptr); }


};

template<typename T>
Tree<T>::Tree(T rootValue, int maxChildren)
        : maxChildren(maxChildren) {
    root = new Node<T>(rootValue,maxChildren);
}

template<typename T>
Tree<T>::Tree(int maxChildren): maxChildren(maxChildren) {}

template<typename T>
Tree<T>::Tree():maxChildren(2) {};

template<typename T>
Tree<T>::~Tree() {
    delete root;
}

template<typename T>
int Tree<T>::add_root(Node<T> *newRoot) {
    if (newRoot->getMaxChildren() != maxChildren) {
        throw std::runtime_error("The node is not fit to this tree with its max children ");
    }

    if (!root)
        root = newRoot;
    else {
        newRoot->addChild(root);
        root = newRoot;
    }
    return 0;
}

template<typename T>
Node<T> *Tree<T>::getRoot() const {
    return root;
}

template<typename T>
int Tree<T>::add_sub_node(Node<T> *dad, Node<T> *child) {
    if (child->getMaxChildren() != maxChildren)
        throw std::runtime_error("The node maximum children number is not fit to this tree");
    dad->addChild(child);
    return 0;
}

template<typename T>
void Tree<T>::drawTree(wxDC &dc, int x, int y, int width, int height) {
    if (root) {
        drawNode(dc, root, x, y, width, height);
    }
}

template<typename T>
void Tree<T>::drawNode(wxDC &dc, Node<T> *node, int x, int y, int width, int height) {
    if (!node) return;

    // Draw the node value
    T nodeValue = node->getValue();
    std::ostringstream oss;
    oss << nodeValue;
    std::string str = oss.str();
    wxString wxStr(str);
    dc.DrawText(wxStr, x, y);

    int numChildren = node->getCurNumOfChildren();
    int childWidth = width / (numChildren + 1);
    int childX = x - (numChildren * childWidth /2 -(childWidth/2));

    for (Node<T> *child : node->getChildren()) {
        int childY = y + 50;  // Adjust the vertical distance between levels as needed
        dc.DrawLine(x + 10, y + 20, childX + 10, childY);  // Draw a line to the child
        drawNode(dc, child, childX, childY, childWidth, height);
        childX += childWidth;
    }
}

#endif //CPP_EX4_TREE_HPP
