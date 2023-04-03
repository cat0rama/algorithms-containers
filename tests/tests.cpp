// #include <iostream>

// void f() {
//     class Test {
//     public:
//         Test(int _a, std::string): a(_a) {
//             a = _a;
//         }


//         int getA() {
//             return a;
//         }

//         ~Test() {
//         }
//     public:
//         int *ptr;
//         int a;
//     };

//         // Компайл тайм тестики
//         static_assert(std::is_same_v<vector<int>::const_pointer, const int*>);
//         static_assert(std::is_same_v<vector<int>::const_iterator::meta_pointer, const int*>);
//         static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int&>);

//         //    vector<double> d(5);

//         //    d.Fill(4);

//         //    vector<double> l(d);

//         //    d = l;

//         //    vector<double> f(200, 5);

//         //    l = vector<double>(10) = f;

//         //    std::vector<int> k;

//         //    auto c = k.begin();
//         //    c = std::move(k.end());

//         //    auto n = l.begin();
//         //    auto m = l.end();
//         //    n = m;

//         //    vector<int> i(10, 4);

//         //    i.data()[10] = 9;

//     //    vector<int> a(10);
//     //    a = vector<int>(23);

//     //    vector<int> l(20);

//     //    a = l;
//     //    a = vector<int>(5, 3);
//     //    a.fill(10);

//     //    std::for_each(a.begin(), a.end(), [](int a) { std::cout << a; });


//     //    vector<Test> a(10);

//     //    a.emplace_back(3, "hello");
//     //    a.emplace_back(10, "lol");

//     //    std::for_each(a.begin(), a.end(), [](auto& a) { std::cout << a.a << ' '; });

// }


// /*
//     AVLNode<Test> c(Test(3));
//     AVLNode<Test> d(Test(10), nullptr, nullptr);

//     std::cout << d.m_val.a;*/

//     vector<Test> a(10);
//     a.push_back(Test(3));

//     vector<Test> c = a;


//     //std::for_each(c.begin(), c.end(), [](auto l){std::cout << l.a; });

//     //std::vector<int> k(10, 4);

//     std::list<int> k = {1,2,3,4};

//     vector l(k.begin(), k.end());

//     l.push_back(5);

// //    std::for_each(l.begin(), l.end(), [](auto l){std::cout << l; });

//     AVLNode<int> f;

//     BSTree<double> tree(3);

//     tree.insert(5);
//     tree.insert(2);
//     tree.insert(9);
//     tree.insert(8);
//     tree.insert(4);

//     tree.erase(3);
//     tree.print();
//     std::cout << std::endl << tree.getMax()->m_val << std::endl;

#include <gtest/gtest.h>



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}