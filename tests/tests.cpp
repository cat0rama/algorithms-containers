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
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <vector>

#include "AVLTree.hpp"
#include "vector.hpp"
#include "tests.hpp"

using namespace own;

TEST(VECTOR_CONSTRUCTOR_TESTS, DEFAULT_CONSTRUCTOR_TEST) {
    vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), DEFAULT_CAPACITY);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, CONSTRUCTOR_WITH_SIZE) {
    vector<int> vec2(50);

    EXPECT_EQ(vec2.size(), 0);
    EXPECT_EQ(vec2.capacity(), 50 * FACTOR);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, CONSTRUCT_WITH_FILL_ELEMENTS) {
    vector<int> vec2(50, 50);

    EXPECT_EQ(vec2.size(), 50);
    EXPECT_EQ(vec2.capacity(), 50 * FACTOR);
    EXPECT_EQ(vec2.at(45), 50);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, INITIALIZER_CONSTRUCTOR) {
    vector<int> vec = {1, 2, 3, 4};
    std::vector<int> vec2 = {1, 2, 3, 4};

    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 4 * FACTOR);

    auto res1 = std::equal(vec.begin(), vec.end(), vec2.begin());
    ASSERT_EQ(res1, true);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, ITERATOR_CONSTRUCTOR) {
    vector<int> vec = {1,2,3,4,5};

    vector vec3(vec.begin(), vec.end());

    EXPECT_EQ(vec3.size(), 5);
    EXPECT_EQ(vec3.capacity(), 10);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, COPY_CONSTRUCTOR_AND_OPERATOR) {
    ::Test l(43);
    vector<::Test> test = {::Test(1), l};
    decltype(test) test2;

    test2 = test;

    ASSERT_EQ(test[0].a, 1);
    ASSERT_EQ(test[1].a, 43);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, MOVE_CONSTRUCTOR_AND_OPERATOR) {
    vector<int> test(vector<int>(10, 5));

    test = vector(vector({1,2,3,4,5}));

    ASSERT_EQ(test[4], 5);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, INDEX_OPERATOR_TEST) {
    vector<int> vec = {1,2,3,4,5,6};

    EXPECT_THROW(vec[75], std::out_of_range);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, SAFE_CPY_TEST) {

}

int main(int argc, char **argv) {
    static_assert(std::is_same_v<vector<int>::const_pointer, const int*>, "Pointer(const) types are not equal.");
    static_assert(std::is_same_v<vector<int>::pointer, int*>, "Pointer types are not equal.");
    static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int&>, "References types are not equal.");
    static_assert(std::is_same_v<vector<int>::const_iterator::meta_reference, const int&>, "References(const) types are not equal.");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
