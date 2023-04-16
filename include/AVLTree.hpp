#ifndef AVLTREE_HPP_H
#define AVLTREE_HPP_H

#include "BSTree.hpp"

namespace own {
template <typename T> struct AVLNode : public TreeNode<T> {
    constexpr AVLNode() noexcept : TreeNode<T>() {}

    template <typename TT,
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit AVLNode(TT&& t_val) : TreeNode<T>(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr AVLNode(TT&& t_val, AVLNode* t_left, AVLNode* t_right)
        : TreeNode<T>(std::forward<TT>(t_val), t_left, t_right) {}

    constexpr AVLNode(AVLNode&& t_node) noexcept : TreeNode<T>(std::move(t_node)) {
        *this = std::move(t_node);
    }

  public:
    AVLNode& operator=(TreeNode<T>&& t_node) noexcept override {
        if (this != &t_node) {
            TreeNode<T>::operator=(std::move(t_node));
            // m_height = std::exchange(t_node.m_height, 0);
            // m_key = std::exchange(t_node.m_key, 0);
        }

        return *this;
    }

  public:
    std::size_t m_height = defines::DEFAULT_HEIGHT;
    std::uint8_t m_key;
};

template <typename T> class AVLTree : public BSTree<T> {
  public:
    constexpr AVLTree() noexcept : BSTree<T>() {}

    constexpr AVLTree(const std::initializer_list<T>& t_list) : BSTree<T>(t_list) {}

    template <typename U,
              typename = std::enable_if_t<std::is_base_of_v<BSTree<T>, std::remove_reference_t<U>>>>
    explicit AVLTree(U&& t_tree) : BSTree<T>(std::forward<U>(t_tree)) {}

    virtual ~AVLTree() {}

  public:
    AVLTree<T>& operator=(const BSTree<T>& t_tree) override {
        if (this != &t_tree) {
            BSTree<T>::operator=(t_tree);
            // m_height = t_tree.m_height;
            // m_key = t_tree.m_key;
        }

        return *this;
    }

    AVLTree<T>& operator=(BSTree<T>&& t_tree) noexcept override {
        if (this != &t_tree) {
            BSTree<T>::operator=(std::move(t_tree));
            // m_height = std::exchange(t_tree.m_height, 0);
            // m_key = std::exchange(t_tree.m_key, 0);
        }

        return *this;
    }

  public:

  protected:
};

} // namespace own

#endif
