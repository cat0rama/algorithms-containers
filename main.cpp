#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <set>

#include "vector.hpp"
#include "set.hpp"

using namespace own;

class Test {
 public:
    Test() = default;

    Test(int _a): a(_a) {
         a = _a;
     }

    Test(Test&& c){ a = c.a;}

    Test(const Test& e) {
        a = e.a;
    };

    Test& operator=(Test&& elem) {
        a = elem.a;
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
    AVLNode<Test> c(Test(3));
    AVLNode<Test> d(std::move(c));

    std::cout << d.m_val.a;
}
