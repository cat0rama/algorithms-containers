#include <gtest/gtest.h>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <vector>

#include "../include/vector.hpp"
#include "../include/AVLTree.hpp"
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
    ASSERT_EQ(vec[4], 5);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, SAFE_CPY_TEST) {
    TestOther<vector<::Test>> test;
    vector<::Test> vec = {::Test(4), ::Test(5), ::Test(10)};
    vector<::Test> vec2;

    // переделать функцию safe_cpy для работы через итераторы

    //test.safe_cpy(vec.begin(), vec2.begin(), vec.size());
}

int main(int argc, char **argv) {
    static_assert(std::is_same_v<vector<int>::const_pointer, const int*>, "Pointer(const) types are not equal.");
    static_assert(std::is_same_v<vector<int>::pointer, int*>, "Pointer types are not equal.");
    static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int&>, "References types are not equal.");
    static_assert(std::is_same_v<vector<int>::const_iterator::meta_reference, const int&>, "References(const) types are not equal.");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
