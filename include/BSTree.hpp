#ifndef BSTREE_HPP_H
#define BSTREE_HPP_H

#include "ITree.hpp"
#include "traits.hpp"

#include <iostream>
#include <optional>
#include <utility>

// подумать насчет конструктора от Args...
// обернуть все в optional

namespace own {
template <typename T> struct TreeNode : public INode {
    constexpr TreeNode() noexcept : m_val(T()), m_left(nullptr), m_right(nullptr) {}

    template <typename TT, /* диспатчу forward reference чтобы чтобы производные классы корректно
    могли перемещаться через move конструктор (https://godbolt.org/z/Efvj1eb1G) */
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit TreeNode(TT&& t_val) : m_val(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr TreeNode(TT&& t_val, TreeNode* t_left, TreeNode* t_right)
        : m_val(std::forward<TT>(t_val)), m_left(t_left), m_right(t_right) {}

    constexpr TreeNode(TreeNode&& t_node) noexcept { *this = std::move(t_node); }

    TreeNode& operator=(TreeNode&& t_node) noexcept {
        if (this != &t_node) {
            static_assert(std::is_move_assignable_v<T> || std::is_move_constructible_v<T>,
                          "object cannot be moved.\n");
            m_val = std::exchange(t_node.m_val, T());
            m_left = std::exchange(t_node.m_left, nullptr);
            m_right = std::exchange(t_node.m_right, nullptr);
        }

        return *this;
    }

  public:
    T m_val;
    TreeNode* m_left;
    TreeNode* m_right;
};

template <typename T> class BSTree : public base_traits<T> {
  protected:
    using base_traits<T>::value_type;
    using base_traits<T>::pointer;
    using base_traits<T>::reference;
    using base_traits<T>::const_pointer;
    using base_traits<T>::const_reference;
    using base_traits<T>::difference_type;
    using node = TreeNode<T>;

  public:
    constexpr BSTree() noexcept : m_root(nullptr) {}

    template <typename U> constexpr BSTree(U&& t_val) { m_root = new_node(std::forward<U>(t_val)); }

    //написать move ctor и copy ctor(операторы в том числе)

    virtual ~BSTree() {
        // удаляем ноды через post_order обход и лямбду которая удаляет ноды
        post_order(m_root, [](auto&& t_node) { delete t_node; });
    }

  public:
    template <typename U> node* new_node(U&& t_elem) const {
        return new node(std::forward<U>(t_elem), nullptr, nullptr);
    }

    template <typename... Args> node* construct_node(Args... t_args) const {
        return new node(T(std::forward<Args>(t_args)...), nullptr, nullptr);
    }

    const node* getMin() const noexcept {
        node* current = m_root;
        while (current && current->m_left != nullptr) {
            current = current->m_left;
        }

        return current;
    }

    const node* getMax() const noexcept {
        node* current = m_root;
        while (current && current->m_right != nullptr) {
            current = current->m_right;
        }

        return current;
    }

    // iterative insert
    template <typename U> constexpr void insert(U&& t_elem) {
        node* new_nd = new_node(std::forward<U>(t_elem));
        node* start = m_root;
        node* to_start = nullptr;

        while (start != nullptr) {
            to_start = start;
            if (t_elem < start->m_val) {
                start = start->m_left;
            } else {
                start = start->m_right;
            }
        }

        if (to_start == nullptr) {
            to_start = new_nd;
        } else if (t_elem < to_start->m_val) {
            to_start->m_left = new_nd;
        } else {
            to_start->m_right = new_nd;
        }
    }

    // iterative delete.
    void erase(const T& t_elem) {
        node* curr = m_root;
        node* prev = nullptr;

        while (curr != nullptr && curr->m_val != t_elem) {
            prev = curr;
            if (t_elem < curr->m_val) {
                curr = curr->m_left;
            } else {
                curr = curr->m_right;
            }
        }

        // if not found
        if (curr == nullptr) {
            return;
        }

        if (curr->m_left == nullptr || curr->m_right == nullptr) {
            node* new_curr = nullptr;
            if (curr->m_left == nullptr) {
                new_curr = curr->m_right;
            } else {
                new_curr = curr->m_left;
            }

            if (prev == nullptr) {
                return;
            }

            if (curr == prev->m_left) {
                prev->m_left = new_curr;
            } else {
                prev->m_right = new_curr;
            }

            delete curr;
        } else {
            node* prev_tmp = nullptr;
            node* tmp = nullptr;

            tmp = curr->m_right;
            while (tmp->m_left != nullptr) {
                prev_tmp = tmp;
                tmp = tmp->m_left;
            }

            if (prev_tmp != nullptr) {
                prev_tmp->m_left = tmp->m_right;
            } else {
                curr->m_right = tmp->m_right;
            }

            curr->m_val = tmp->m_val;
            delete tmp;
        }
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

    // проверить на наличие перегруженного оператора <<
    void print() {
        // пока что так
        static_assert(std::is_arithmetic_v<T>, "arithmetic type required.\n");
        inorder(m_root, [](auto&& t_node) { std::cout << t_node->m_val; });
    }

    constexpr node* getRoot() const noexcept { return m_root; }

  protected:
    node* m_root;
};
} // namespace own

#endif
