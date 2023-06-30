#include "tests.hpp"

#include <gtest/gtest.h>
#include <algorithm>
#include <type_traits>
#include <vector>

using namespace s21;

TEST(VECTOR_CONSTRUCTOR_TESTS, DEFAULT_CONSTRUCTOR_TEST) {
  vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), DEFAULT_CAPACITY * FACTOR);
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
  vector<int> vec = {1, 2, 3, 4, 5};

  vector vec3(vec.begin(), vec.end());

  EXPECT_EQ(vec3.size(), 5);
  EXPECT_EQ(vec3.capacity(), 10);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, COPY_CONSTRUCTOR_AND_OPERATOR) {
  ::Test l(43);
  vector<::Test> test{::Test(1), l};
  decltype(test) test2;

  test2 = test;

  ASSERT_EQ(test[0].a, 1);
  ASSERT_EQ(test[1].a, 43);
}

TEST(VECTOR_CONSTRUCTOR_TESTS, MOVE_CONSTRUCTOR_AND_OPERATOR) {
  vector<int> test(vector<int>(10, 5));

  test = vector(vector({1, 2, 3, 4, 5}));

  ASSERT_EQ(test[4], 5);
}

TEST(VECTOR_FUNCTION_TESTS, INDEX_OPERATOR_TEST) {
  vector<int> vec = {1, 2, 3, 4, 5, 6};

  EXPECT_THROW(vec[75], std::out_of_range);
  ASSERT_EQ(vec[4], 5);
}

TEST(VECTOR_FUNCTION_TESTS, METHOD_AT_TEST) {
  vector<int> vec = {1, 2, 3, 4, 5, 6};

  EXPECT_THROW(vec.at(75), std::out_of_range);
  ASSERT_EQ(vec.at(3), 4);
}

TEST(VECTOR_FUNCTION_TESTS, METHOD_FILL_TEST) {
  vector<int> vec(10);
  vec.fill(3);

  std::for_each(vec.begin(), vec.end(), [](auto elem) { ASSERT_EQ(elem, 3); });
}

TEST(VECTOR_FUNCTION_TESTS, METHOD_CLEAR_TEST) {
  vector<::Test> vec;
  vec.push_back(::Test(4));
  vec.push_back(::Test(6));
  vec.clear();

  ASSERT_EQ(vec.size(), 0);
}

TEST(ALL, CONTAINERS_TEST) {
  // AVLTree<int> a;
  // a.Insert(4);
  const queue<int> l = {1, 2, 3, 4, 5};

  // std::for_each(l.begin(), l.end(), [](auto elem){ std::cout << elem <<
  // std::endl; });

  queue<int> c = {1, 2, 3, 4, 5};

  c.pop();
  c.pop();

  std::for_each(c.begin(), c.end(),
                [](auto elem) { std::cout << elem << std::endl; });

  stack<int> st;

  std::cout << "stack: " << std::endl;

  st.push(3);
  st.push(4);
  st.push(5);
  st.pop();
  st.push(7);
  st.push(9);

  std::cout << "top: " << st.top() << std::endl;

  std::for_each(st.begin(), st.end(),
                [](auto elem) { std::cout << elem << std::endl; });

  AVLTree<int> avl;

  avl.insert(avl.get_root(), 3);

  avl.insert(avl.get_root(), 5);

  avl.insert(avl.get_root(), 6);

  avl.print();

}

int main(int argc, char **argv) {
  static_assert(std::is_same_v<vector<int>::const_pointer, const int *>,
                "Pointer(const) types are not equal.");
  static_assert(std::is_same_v<vector<int>::pointer, int *>,
                "Pointer types are not equal.");
  static_assert(std::is_same_v<vector<int>::iterator::meta_reference, int &>,
                "References types are not equal.");
  static_assert(
      std::is_same_v<vector<int>::const_iterator::meta_reference, const int &>,
      "References(const) types are not equal.");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
