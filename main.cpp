#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <list>

#include "vector.hpp"
#include "set.hpp"
#include "BSTree.hpp"
#include "AVLTree.hpp"
#include "tests/tests.hpp"

using namespace own;

int main() {
    int a = 4;
    BSTree<int> tree = {1,2,3, a};

    tree.insert(3);
    tree.insert(5);
    tree.insert(8);

    BSTree<int> tree2(tree);

    tree2.print();
}
