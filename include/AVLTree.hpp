#ifndef AVLTREE_HPP_H
#define AVLTREE_HPP_H

#include "BSTree.hpp"
#include "AVLNode.hpp"

namespace own {
template <typename T> class AVLTree {
  public:
    using node = AVLNode<T>;

  public:
    constexpr AVLTree() noexcept {}

    constexpr AVLTree(const std::initializer_list<T>& t_list)  {
        //insert(t_list.begin(), t_list.end());
    }

    template <typename U, typename = std::enable_if_t<
                              std::is_base_of_v<AVLTree<T>, std::remove_reference_t<U>>>>
    explicit AVLTree(U&& t_tree) {
        *this = std::forward<U>(t_tree);
    }

    virtual ~AVLTree() {}

  public:
    AVLTree<T>& operator=(const AVLTree<T>& t_tree) {
        if (this != &t_tree) {
            // пока что так
            //BSTree<T>::destroy();
            m_root = copy_tree(t_tree.ptr);
        }

        return *this;
    }

    AVLTree<T>& operator=(AVLTree<T>&& t_tree) noexcept {
        if (this != &t_tree) {
            // пока что так
            //BSTree<T>::destroy();
        }

        return *this;
    }

  protected:
    node* copy_tree(node* t_node) {
        if (t_node == nullptr) {
            return nullptr;
        }

        /*node* nd = static_cast<node*>(new_node(t_node->m_val));
        nd->m_key = t_node->m_key;
        nd->m_height = t_node->m_height;
        nd->m_left = copy_tree(static_cast<node*>(t_node->m_left));
        nd->m_right = copy_tree(static_cast<node*>(t_node->m_right));*/

        return node;
    }

  public:
    void insert(const T& t_elem) {
        // написать вставку с учетом балансировки
    }

    [[nodiscard]] const node* get_root() const noexcept { return m_root; }

    [[nodiscard]] node* get_root() noexcept { return m_root; }

protected:
    node* m_root = nullptr;
};

} // namespace own

#endif
