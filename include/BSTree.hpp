#ifndef BSTREE_HPP_H
#define BSTREE_HPP_H

#include "ITree.hpp"
#include "traits.hpp"

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>

namespace own {
template <typename T> struct TreeNode : public INode {
    constexpr TreeNode() noexcept : m_val(T()), m_left(nullptr), m_right(nullptr) {}

    template <typename TT, /* диспатчу forward reference чтобы чтобы производные классы корректно
    могли перемещаться через move конструктор (https://godbolt.org/z/Efvj1eb1G) */
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit TreeNode(TT&& t_val)
        : m_val(std::forward<TT>(t_val)), m_left(nullptr), m_right(nullptr) {}

    template <typename TT>
    constexpr TreeNode(TT&& t_val, TreeNode* t_left, TreeNode* t_right)
        : m_val(std::forward<TT>(t_val)), m_left(t_left), m_right(t_right) {}

    constexpr TreeNode(TreeNode&& t_node) noexcept { *this = std::move(t_node); }

    virtual ~TreeNode() {}

  public:
    virtual TreeNode& operator=(TreeNode<T>&& t_node) noexcept {
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

template <typename T, class Allocator = std::allocator<T>> class BSTree {
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = typename Allocator::size_type;
    using difference_type = typename Allocator::difference_type;
    using reference = typename Allocator::reference;
    using const_reference = typename Allocator::const_reference;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;
    using node = TreeNode<T>;

  public:
    constexpr BSTree() noexcept {}

    constexpr BSTree(const std::initializer_list<T>& t_list) {
        std::for_each(t_list.begin(), t_list.end(), [&](auto& t_elem) { insert(t_elem); });
    }

    template <typename U,
              typename = std::enable_if_t<std::is_base_of_v<BSTree, std::remove_reference_t<U>>>>
    explicit BSTree(U&& t_tree) {
        *this = std::forward<U>(t_tree);
    }

    virtual ~BSTree() { destroy(); }

  public:
    virtual BSTree<T>& operator=(const BSTree<T>& t_tree) {
        if (this != &t_tree) {
            destroy();
            m_root = copy_tree(t_tree.m_root);
        }

        return *this;
    }

    virtual BSTree<T>& operator=(BSTree<T>&& t_tree) noexcept {
        if (this != &t_tree) {
            destroy();
            m_root = std::exchange(t_tree.m_root, nullptr);
        }

        return *this;
    }

  protected:
    void destroy() noexcept {
        // удаляем ноды через post_order обход и лямбду которая удаляет ноды
        post_order(m_root, [](auto& t_node) { delete t_node; });
    }

  public:
    template <typename U> [[nodiscard]] node* new_node(U&& t_elem) const {
        return new node(std::forward<U>(t_elem));
    }

    template <typename... Args> [[nodiscard]] node* construct_node(Args... t_args) const {
        return new node(T(std::forward<Args>(t_args)...));
    }

    [[nodiscard]] const node* get_min() const noexcept {
        node* current = m_root;
        while (current && current->m_left != nullptr) {
            current = current->m_left;
        }

        return current;
    }

    [[nodiscard]] const node* get_max() const noexcept {
        node* current = m_root;
        while (current && current->m_right != nullptr) {
            current = current->m_right;
        }

        return current;
    }

    // iterative insert
    virtual void insert(const T& t_elem) {
        node* new_nd = new_node(t_elem);

        if (m_root == nullptr) {
            m_root = new_nd;
            return;
        }

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

    // iterative delete
    void erase(const T& t_elem) noexcept {
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

    node* copy_tree(node* t_node) {
        if (t_node == nullptr) {
            return nullptr;
        }

        node* nd = new_node(t_node->m_val);
        nd->m_left = copy_tree(t_node->m_left);
        nd->m_right = copy_tree(t_node->m_right);

        return nd;
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
        inorder(m_root, [](auto&& t_node) { std::cout << t_node->m_val << ' '; });
    }

    [[nodiscard]] constexpr node* get_root() const noexcept { return m_root; }

    MODIFIRE : node* m_root = nullptr;
};
} // namespace own

#endif
