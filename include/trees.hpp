#ifndef TREES_HPP_
#define TREES_HPP_

#include "nodes.hpp"
#include "type_traits.hpp"

#include <iostream>

namespace own {
template <typename T> class BSTree : public base_traits<T> {
    using node = TreeNode<T>;

  public:
    BSTree() noexcept : m_root(nullptr) {}

    template <typename U> BSTree(U&& t_val) { m_root = new_node(std::forward<U>(t_val)); }

    ~BSTree() {
        // удаляем ноды через post_order обход и лямбду которая удаляет ноды
        post_order(m_root, [](auto t_node) { delete t_node; });
    }

  public:
    template <typename U> node* new_node(U&& t_elem) const {
        return new node(std::forward<U>(t_elem), nullptr, nullptr);
    }

    template <typename U> constexpr void insert_recursion(node*& t_root, U&& t_elem) {
        if (t_root == nullptr) {
            t_root = new_node(std::forward<U>(t_elem));
            return;
        }

        if (m_root->m_val > t_elem) {
            insert_recursion(t_root->m_left, std::forward<U>(t_elem));
        } else {
            insert_recursion(t_root->m_right, std::forward<U>(t_elem));
        }
    }

    template <typename U> constexpr void insert(U&& t_elem) {
        insert_recursion(m_root, std::forward<U>(t_elem));
    }

    template <typename Func> constexpr void post_order(node* t_root, Func t_fn) {
        if (t_root != nullptr) {
            post_order(t_root->m_left, t_fn);
            post_order(t_root->m_right, t_fn);
            t_fn(t_root);
        }
    }

    template <typename Func> constexpr void inorder(node* t_root, Func t_fn) {
        if (t_root != nullptr) {
            inorder(t_root->m_left, t_fn);
            t_fn(t_root);
            inorder(t_root->m_right, t_fn);
        }
    }

    void print() {
        static_assert(std::is_arithmetic_v<T>, "arithmetic type required.");
        post_order(m_root, [](auto t_node) { std::cout << t_node->m_val; });
    }

    constexpr node* get_root() const noexcept { return m_root; }

  public:
    node* m_root;
};
} // namespace own

#endif
