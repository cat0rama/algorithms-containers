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

int main() {
    std::vector<int> vec = {1,2,3,4,5, 6, 7, 8, 9, 10};
    vector<int> vec2 = {1,2,3,4,5, 6, 7, 8, 9, 10};

    std::cout << vec.capacity() << std::endl;
    std::cout << vec2.capacity() << std::endl;

    vec.shrink_to_fit();
    vec2.shrink_to_fit();

    for (auto&& e : vec) {
        std::cout << e << " ";
    }

    std::cout << "\n\n\n";

    for (auto&& e : vec2) {
        std::cout << e << " ";
    }


    std::cout << "\n\n\n";

    std::cout << vec.capacity() << std::endl;
    std::cout << vec2.capacity() << std::endl;
}
