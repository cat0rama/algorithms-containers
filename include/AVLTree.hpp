#ifndef AVLTREE_HPP_H
#define AVLTREE_HPP_H

#include "BSTree.hpp"

namespace own {
template <typename T> struct AVLNode : public TreeNode<T> {
    constexpr AVLNode() noexcept : TreeNode<T>(), m_height(defines::DEFAULT_HEIGHT) {}

    template <typename TT,
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit AVLNode(TT&& t_val) : TreeNode<T>(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr AVLNode(TT&& t_val, AVLNode* t_left, AVLNode* t_right)
        : TreeNode<T>(std::forward<TT>(t_val), t_left, t_right) {}

    constexpr AVLNode(AVLNode&& t_node) noexcept : TreeNode<T>(std::move(t_node)) {
        *this = std::move(t_node);
    }

    AVLNode& operator=(AVLNode&& t_node) noexcept {
        if (this != &t_node) {
            TreeNode<T>::operator=(std::move(t_node));
            m_height = std::exchange(t_node.m_height, 0);
        }

        return *this;
    }

  public:
    std::uint8_t m_height;
};

template <typename T> class AVLTree : public BSTree<T> {
  public:
    constexpr AVLTree() noexcept : BSTree<T>() {}

    constexpr AVLTree(const std::initializer_list<T>& t_list): BSTree<T>(t_list) {}

    template <typename U, typename = std::enable_if_t<std::is_base_of_v<BSTree<T>, std::remove_reference_t<U>>>>
    explicit AVLTree(U&& t_tree) {}

    virtual ~AVLTree() {}
  public:
    template <typename U, typename = std::enable_if_t<std::is_base_of_v<BSTree<T>, std::remove_reference_t<U>>>>
    AVLTree<T>& operator=(U&& t_tree) {
        if (this != &t_tree) {
            BSTree<T>::operator=(t_tree);
        }

        return *this;
    }
  protected:
    //std::size_t m_hight;
};

} // namespace own

#endif
