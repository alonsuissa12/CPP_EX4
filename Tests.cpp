// 211344015 alonsuissa12@gmai.com
// Created by alon on 6/27/24.
//
#include "doctest.h"
#include "Node.hpp"
#include "Tree.hpp"

using namespace doctest;
using namespace std;


// ##################################### - NODE - #####################################

TEST_CASE("default maxChildren in Node") {
    Node<double> *n1 = new Node<double>(1.1);
    CHECK_EQ(n1->getMaxChildren(), 2);

    Node<string> *n2 = new Node<string>("str");
    CHECK_EQ(n2->getMaxChildren(), 2);
}

TEST_CASE("maxChildren in Node") {
    Node<double> *n1 = new Node<double>(12, 1.1);
    CHECK_EQ(n1->getMaxChildren(), 12);

    Node<string> *n2 = new Node<string>(13, "str");
    CHECK_EQ(n2->getMaxChildren(), 13);
}

TEST_CASE("current number of children in Node on creating") {
    Node<double> *n1 = new Node<double>(12, 1.1);
    CHECK_EQ(n1->getCurNumOfChildren(), 0);
}

TEST_CASE("current number of children in Node after adding") {
    Node<double> *n1 = new Node<double>(12, 1.1);
    for (int i = 0; i < 9; ++i) {
        n1->addChild(new Node<double>(12, 2.2));
        CHECK_EQ(n1->getCurNumOfChildren(), i + 1);
    }
}

TEST_CASE("get value of node") {
    for (int i = 0; i < 9; ++i)
        CHECK_EQ((Node<int>(5, i).getValue()), i);
}

TEST_CASE("add children") {
    Node<string> *n1 = new Node<string>(12, "hello");
    Node<string> *child1 = new Node<string>(12, "w");
    Node<string> *child2 = new Node<string>(12, "o");
    Node<string> *child3 = new Node<string>(12, "r");
    Node<string> *child4 = new Node<string>(12, "l");
    Node<string> *child5 = new Node<string>(12, "d");
    n1->addChild(child1);
    n1->addChild(child2);
    n1->addChild(child3);
    n1->addChild(child4);
    n1->addChild(child5);

    vector<Node<string> *> comp;
    comp.push_back(child1);
    comp.push_back(child2);
    comp.push_back(child3);
    comp.push_back(child4);
    comp.push_back(child5);

    for (int i = 0; i < 5; ++i) {
        CHECK_EQ(n1->getChildren()[i], comp[i]);
    }

}

TEST_CASE("try to add to many children to node") {
    Node<string> *n1 = new Node<string>(2, "hello");
    Node<string> *child1 = new Node<string>(2, "w");
    Node<string> *child2 = new Node<string>(2, "o");
    Node<string> *child3 = new Node<string>(2, "r");
    Node<string> *child4 = new Node<string>(2, "l");
    n1->addChild(child1);
    n1->addChild(child2);
    CHECK_THROWS(n1->addChild(child3));
    CHECK_THROWS(n1->addChild(child4));
}

TEST_CASE("operator == of node") {
    Node<string> n1(2, "w");
    Node<string> n2(2, "w");
    Node<string> n3(2, "me");
    CHECK((n1 == n2));
    CHECK_FALSE((n1 == n3));
}

TEST_CASE("operator != of node") {
    Node<string> n1(2, "me");
    Node<string> n2(2, "imposter");
    Node<string> n3(2, "me");
    CHECK((n1 != n2));
    CHECK_FALSE((n1 != n3));
}

// ##################################### - TREE - #####################################

TEST_CASE("root value") {
    Tree<int> t1(2, 4);
    Tree<int> t2(5, 1);
    CHECK_EQ(t1.getRoot()->getValue(), 2);
    CHECK_EQ(t2.getRoot()->getValue(), 5);
}

TEST_CASE("root max children") {
    Tree<int> t1(2, 4);
    Tree<int> t2(5, 1);
    CHECK_EQ(t1.getRoot()->getMaxChildren(), 4);
    CHECK_EQ(t2.getRoot()->getMaxChildren(), 1);
}

TEST_CASE("tree max children") {
    Tree<int> t1(2, 4);
    Tree<int> t2(5, 1);
    CHECK_EQ(t1.getMaxChildren(), 4);
    CHECK_EQ(t2.getMaxChildren(), 1);
}

TEST_CASE("tree default max children") {
    Tree<int> *t1 = new Tree<int>();
    CHECK_EQ(t1->getMaxChildren(), 2);
}

TEST_CASE("add root to an empty tree") {
    Tree<string> *t1 = new Tree<string>();
    Node<string> *n1 = new Node<string>(2, "hello");
    t1->add_root(n1);
    CHECK_EQ(t1->getRoot(), n1);
}

TEST_CASE("add root to non-empty tree") {
    Tree<string> *t1 = new Tree<string>("root", 2);
    Node<string> *n1 = new Node<string>(2, "new root");
    t1->add_root(n1);
    CHECK_EQ(t1->getRoot(), n1);
}

TEST_CASE("add not fit root") {
    Tree<string> *t1 = new Tree<string>("root", 4);
    Node<string> *n1 = new Node<string>(2, "new root");
    CHECK_THROWS(t1->add_root(n1));
}

TEST_CASE("add sub node ") {
    Tree<int> t1(0, 2);
    Node<int> *n1 = new Node<int>(2, 1);
    Node<int> *n2 = new Node<int>(2, 2);

    CHECK_NOTHROW(t1.add_sub_node(t1.getRoot(), n1));
    CHECK_NOTHROW(t1.add_sub_node(t1.getRoot(), n2));

    vector<Node<int> *> comp;
    comp.push_back(n1);
    comp.push_back(n2);
    CHECK_EQ(t1.getRoot()->getChildren(), comp);

}

TEST_CASE("add sub node-  not enough space") {
    Tree<int> t1(0, 2);
    Node<int> *n1 = new Node<int>(2, 1);
    Node<int> *n2 = new Node<int>(2, 2);
    Node<int> *n3 = new Node<int>(2, 3);

    CHECK_NOTHROW(t1.add_sub_node(t1.getRoot(), n1));
    CHECK_NOTHROW(t1.add_sub_node(t1.getRoot(), n2));
    CHECK_THROWS(t1.add_sub_node(t1.getRoot(), n3));
}

TEST_CASE("add sub node - maximum number child too big") {
    Tree<int> t1(0, 2);
    Node<int> *n1 = new Node<int>(20, 1);
    CHECK_THROWS(t1.add_sub_node(t1.getRoot(), n1));

}

TEST_CASE("add sub node - maximum number child too small") {
    Tree<int> t1(0, 2);
    Node<int> *n1 = new Node<int>(1, 1);
    CHECK_THROWS(t1.add_sub_node(t1.getRoot(), n1));
}

// ##################################### - ITERATORS - #####################################

TEST_CASE("DFS Iterator Test") {
    Tree<int> tree(1, 2);
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);
    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));
    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    std::vector<int> expected = {1, 3, 7, 6, 2, 5, 4};
    std::vector<int> result;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("DFS Iterator Test - big tree") {
    Tree<int> tree(1, 2);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));

    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 15));

    std::vector<int> expected = {1, 3, 7, 11, 10, 6, 9, 8, 2, 5, 15, 14, 4, 13, 12};
    std::vector<int> result;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); it++) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("PreOrder Iterator Test") {
    Tree<int> tree(1, 2);
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);
    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));
    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    std::vector<int> expected = {1, 2, 4, 5, 3, 6, 7};
    std::vector<int> result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("PreOrder Iterator Test - big tree") {
    Tree<int> tree(1, 2);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));

    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 15));

    std::vector<int> expected = {1, 2, 4, 12, 13, 5, 14, 15, 3, 6, 8, 9, 7, 10, 11};
    std::vector<int> result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("PostOrder Iterator Test") {
    Tree<int> tree(1, 2);
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);
    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));
    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    std::vector<int> expected = {4, 5, 2, 6, 7, 3, 1};
    std::vector<int> result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("postOrder Iterator Test - big tree") {
    Tree<int> tree(1, 2);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));

    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 15));

    std::vector<int> expected = {12, 13, 4, 14, 15, 5, 2, 8, 9, 6, 10, 11, 7, 3, 1};
    std::vector<int> result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("InOrder Iterator Test") {
    Tree<int> tree(1, 2);
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);
    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));
    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    std::vector<int> expected = {4, 2, 5, 1, 6, 3, 7};
    std::vector<int> result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("inOrder Iterator Test - big tree") {
    Tree<int> tree(1, 2);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));

    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 15));

    std::vector<int> expected = {12, 4, 13, 2, 14, 5, 15, 1, 8, 6, 9, 3, 10, 7, 11};
    std::vector<int> result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("BFS Iterator Test") {
    Tree<int> tree(1, 2);
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);
    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));
    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> result;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

TEST_CASE("BFS Iterator Test - big tree") {
    Tree<int> tree(1, 2);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(2, 2);
    Node<int> *right = new Node<int>(2, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(2, 4));
    tree.add_sub_node(left, new Node<int>(2, 5));

    tree.add_sub_node(right, new Node<int>(2, 6));
    tree.add_sub_node(right, new Node<int>(2, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(2, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(2, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(2, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(2, 15));

    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15, 8, 9, 10, 11};
    std::vector<int> result;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);
}

// should behave like DFS
TEST_CASE("PreOrder Iterator Test - non binary") {
    Tree<int> tree(1, 3);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(3, 2);
    Node<int> *right = new Node<int>(3, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(3, 4));
    tree.add_sub_node(left, new Node<int>(3, 5));

    tree.add_sub_node(right, new Node<int>(3, 6));
    tree.add_sub_node(right, new Node<int>(3, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(3, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(3, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(3, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(3, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(3, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(3, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(3, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(3, 15));

    std::vector<int> expected = {1, 3, 7, 11, 10, 6, 9, 8, 2, 5, 15, 14, 4, 13, 12};
    std::vector<int> result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); it++) {
        result.push_back((*it)->getValue());

    }

    CHECK_EQ(result, expected);

}

// should behave like DFS
TEST_CASE("PostOrder Iterator Test - non binary(big tree)") {
    Tree<int> tree(1, 3);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(3, 2);
    Node<int> *right = new Node<int>(3, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(3, 4));
    tree.add_sub_node(left, new Node<int>(3, 5));

    tree.add_sub_node(right, new Node<int>(3, 6));
    tree.add_sub_node(right, new Node<int>(3, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(3, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(3, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(3, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(3, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(3, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(3, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(3, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(3, 15));

    std::vector<int> expected = {1, 3, 7, 11, 10, 6, 9, 8, 2, 5, 15, 14, 4, 13, 12};
    std::vector<int> result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); it++) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);

}

// should behave like DFS
TEST_CASE("inOrder Iterator Test - non binary (big tree)") {
    Tree<int> tree(1, 3);

    // Adding nodes to create a tree with 15 nodes
    Node<int> *root = tree.getRoot();
    Node<int> *left = new Node<int>(3, 2);
    Node<int> *right = new Node<int>(3, 3);
    tree.add_sub_node(root, left);
    tree.add_sub_node(root, right);

    tree.add_sub_node(left, new Node<int>(3, 4));
    tree.add_sub_node(left, new Node<int>(3, 5));

    tree.add_sub_node(right, new Node<int>(3, 6));
    tree.add_sub_node(right, new Node<int>(3, 7));

    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(3, 8));
    tree.add_sub_node(right->getChildren()[LEFT_CHILD], new Node<int>(3, 9));

    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(3, 10));
    tree.add_sub_node(right->getChildren()[RIGHT_CHILD], new Node<int>(3, 11));

    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(3, 12));
    tree.add_sub_node(left->getChildren()[LEFT_CHILD], new Node<int>(3, 13));

    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(3, 14));
    tree.add_sub_node(left->getChildren()[RIGHT_CHILD], new Node<int>(3, 15));

    std::vector<int> expected = {1, 3, 7, 11, 10, 6, 9, 8, 2, 5, 15, 14, 4, 13, 12};
    std::vector<int> result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); it++) {
        result.push_back((*it)->getValue());
    }

    CHECK_EQ(result, expected);

}


