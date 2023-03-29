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

using namespace own;

class Test {
 public:
    Test() {
        std::cout << "construct" << std::endl;
    }

    Test(std::string, int) {
        std::cout << "string:int" << std::endl;
    }

    Test(int _a): a(_a) {
         a = _a;
     }

    Test(Test&& c) {

    }

    Test(const Test& e) {
        a = e.a;
    };

    Test& operator=(const Test& elem) {
        a = elem.a;
        return *this;
    }

    Test& operator=(Test&&) {return *this;};

    friend bool operator>(const Test& a, const Test& b) {
        return a.a > b.a;
    }

     int getA() {
         return a;
     }

     ~Test() = default;
 public:
     int a;
 };

int main()
{
    BSTree<Test> bst;
    AVLTree<Test> dl;

    auto node = bst.new_node(std::string("hello"), 3);
}
