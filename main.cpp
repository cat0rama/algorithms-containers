#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <set>

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

    Test(int _a): a(_a) {
         a = _a;
     }

    Test(Test&& c){ a = c.a;}

    Test(const Test& e) {
        a = e.a;
    };

    Test& operator=(const Test& elem) {
        a = elem.a;
        return *this;
    }

    friend bool operator>(const Test& a, const Test& b) {
        return a.a > b.a;
    }

    Test& operator=(Test&& elem) {
        a = elem.a;
        return *this;
    }

     int getA() {
         return a;
     }

     ~Test() = default;
 public:
     int a;
 };

int main()
{/*
    AVLNode<Test> c(Test(3));
    AVLNode<Test> d(Test(10), nullptr, nullptr);

    std::cout << d.m_val.a;*/

//    vector<Test> a(10);
//    a.push_back(Test(3));
//    a.push_back(Test(4));
//    a.push_back(Test(9));

//    vector<Test> c = a;


//    std::for_each(c.begin(), c.end(), [](auto l){std::cout << l.a; });
//    std::cout << std::endl;
//    std::for_each(a.begin(), a.end(), [](auto l){std::cout << l.a; });

    AVLNode<int> f;

    BSTree<double> tree(3);

    tree.insert(5);
    tree.insert(2);
    tree.insert(9);
    tree.insert(8);
    tree.insert(4);

    tree.erase(3);
    tree.print();
    std::cout << std::endl << tree.min()->m_val << std::endl;
}
