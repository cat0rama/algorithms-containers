#ifndef AVLTREE_HPP_H
#define AVLTREE_HPP_H

#include "AVLNode.hpp"
#include "BSTree.hpp"

namespace own {
template <typename T> class AVLTree {
  public:
    using node = AVLNode<T>;

  public:
    constexpr AVLTree() noexcept {}

    constexpr AVLTree(const std::initializer_list<T>& t_list) {
        // insert(t_list.begin(), t_list.end());
    }

    template <typename U, typename = std::enable_if_t<
                              std::is_base_of_v<AVLTree<T>, std::remove_reference_t<U>>>>
    explicit AVLTree(U&& t_tree) {
        *this = std::forward<U>(t_tree);
    }

    virtual ~AVLTree() { destroy(); }

  public:
    AVLTree<T>& operator=(const AVLTree<T>& t_tree) {
        if (this != &t_tree) {
            //
        }

        return *this;
    }

    AVLTree<T>& operator=(AVLTree<T>&& t_tree) noexcept {
        if (this != &t_tree) {
            //
        }

        return *this;
    }

  protected:
    // node* copy_tree(node* t_node) {
    //    if (t_node == nullptr) {
    //        return nullptr;
    //    }

    //    /*node* nd = static_cast<node*>(new_node(t_node->m_val));
    //    nd->m_key = t_node->m_key;
    //    nd->m_height = t_node->m_height;
    //    nd->m_left = copy_tree(static_cast<node*>(t_node->m_left));
    //    nd->m_right = copy_tree(static_cast<node*>(t_node->m_right));*/

    //    return node;
    //}

    void destroy() noexcept {
        if (m_root == nullptr) {
            return;
        }

        BSTree<T>::post_order(m_root, [](auto t_node) { delete t_node; });
    }

  public:
    template <typename YY> [[nodiscard]] node* insert(node* t_node, YY&& t_elem) {
        if (!m_root) {
            return new node(std::forward<YY>(t_elem));
        }

        if (t_elem < t_node->m_val) {
            t_node->m_left = insert(t_node, std::forward<YY>(t_elem));
        } else {
            t_node->m_right = insert(t_node, std::forward<YY>(t_elem));
        }

        return balance(t_node);
    }

    [[nodiscard]] int balance_factor(node* t_node) const {
        if (!t_node) {
            throw std::runtime_error("pointer is not valid.\n");
        }

        return t_node->m_right->m_height - t_node->m_left->m_height;
    }

    void fix_height(node* t_node) const noexcept {
        auto hl = t_node->m_left->m_height;
        auto hr = t_node->m_right->m_height;
        t_node->m_height = (hl > hr ? hl : hr) + 1;
    }

    [[nodiscard]] node* rotate_rigth(node* t_node) noexcept {
        auto tmp = t_node->m_left;
        t_node->m_left = tmp->m_right;
        tmp->m_right = t_node;
        fix_height(t_node);
        fix_height(tmp);
        return tmp;
    }

    [[nodiscard]] node* rotate_left(node* t_node) noexcept {
        auto tmp = t_node->m_right;
        t_node->m_left = tmp->m_left;
        tmp->m_left = t_node;
        fix_height(t_node);
        fix_height(tmp);
        return tmp;
    }

    [[nodiscard]] node* balance(node* t_node) {
        fix_height(t_node);
        if (balance_factor(t_node) == 2) {
            if (balance_factor(t_node->m_right) < 0) {
                t_node->m_right = rotate_rigth(t_node->m_right);
            }
            return rotate_left(t_node);
        }

        if (balance_factor(t_node) == -2) {
            if (balance_factor(t_node->m_left) > 0) {
                t_node->m_left = rotate_left(t_node->m_left);
            }
            return rotate_rigth(t_node);
        }

        return t_node;
    }

    [[nodiscard]] const node* get_root() const noexcept { return m_root; }

    [[nodiscard]] node* get_root() noexcept { return m_root; }

  protected:
    node* m_root = nullptr;
};

} // namespace own

#endif
