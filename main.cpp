#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

#include "vector.hpp"
#include "set.hpp"
#include "BSTree.hpp"
#include "AVLTree.hpp"
#include "tests/tests.hpp"

using namespace own;

int main() {
//    int a = 4;
//    BSTree<int> tree = {1,2,3, a};
//
//    tree.insert(3);
//    tree.insert(5);
//    tree.insert(8);
//
//    BSTree<int> tree2(tree);
//
//    tree2 = BSTree<int>{1,2,3};
//
//    tree2 = tree;
//
//    tree2.print();

    AVLTree<int> ptd;

    BSTree<int>* ptr = new AVLTree<int>(std::move(ptd));

    ptr->insert(3);
    ptr->insert(3);
    ptr->print();

    delete ptr;
    
    TreeNode<int>* tr = new AVLNode<int>;

    *tr = AVLNode<int>(3);

    delete tr;
}
