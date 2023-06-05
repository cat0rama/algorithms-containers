#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "BSTree.hpp"
#include "undordred_map.hpp"
#include "vector.hpp"
#include "set.hpp"
#include "tests/tests.hpp"
#include "AVLTree.hpp"

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


	/*AVLNode<int> a;
	AVLNode<int> b = std::move(a);

	TreeNode<int> k;
    TreeNode<int> l = std::move(k);*/

	//BSTree<int>* tree = new AVLTree<int>;
	//
	//*tree = AVLTree<int>();

	/*avltree<int> tree;
	avltree<int> tree2;
	tree2.insert(3);
    tree2.insert(3);
    tree2.insert(3);
    tree2.insert(9);

	tree = tree2;

	tree.print();*/

	//vector<Test> vec = {Test(1), Test(2), Test(3)};

	//vec.erase(vec.begin());

	//std::for_each(vec.begin(), vec.end(), [](auto elem) { std::cout << elem.a << ' ';
	//});

	//std::cout << std::endl;

	//std::vector<Test> vec2 = {Test(1), Test(2), Test(3)};

 //   vec2.erase(vec2.begin());
	vector<int> vec = {6, 5, 5, 4};

	auto l = vec.emplace(vec.begin(), 1, 2, 3, 4);

	std::for_each(vec.begin(), vec.end(), [](auto elem) { 
		std::cout << elem << ' ';
	});

	//vector<int> lo;

	//lo.swap(vec);

	//std::cout << lo.size() << std::endl;

	/*unordered_map<int, int> d;

	for (int i = 0; i < 64; i++) {
        auto l = d.insert(std::make_pair(i, i + 1));
	}

	for (int i = 0; i < 64; i++) {
        std::cout << d[i] << std::endl;
    }*/
    //auto c = vector<int>::iterator(vec.cbegin());
	
	AVLTree<int> ve;
    auto c = ve.get_root();
    c = ve.insert(ve.get_root(), 3);
}
