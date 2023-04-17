#ifndef AVLTREE_HPP_H
#define AVLTREE_HPP_H

#include "BSTree.hpp"

namespace own {
template <typename T> struct AVLNode : public TreeNode<T> {
    constexpr AVLNode() noexcept : m_key(0), TreeNode<T>() {}

    template <typename TT,
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit AVLNode(TT&& t_val) : TreeNode<T>(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr AVLNode(TT&& t_val, AVLNode* t_left, AVLNode* t_right)
        : TreeNode<T>(std::forward<TT>(t_val), t_left, t_right) {}

    constexpr AVLNode(AVLNode&& t_node) noexcept : TreeNode<T>(std::move(t_node)) {
        m_height = std::exchange(t_node.m_height, 0);
        m_key = std::exchange(t_node.m_key, 0);
    }

  public:
    AVLNode& operator=(AVLNode<T>&& t_node) noexcept {
        if (this != &t_node) {
            m_height = std::exchange(t_node.m_height, 0);
            m_key = std::exchange(t_node.m_key, 0);
            TreeNode<T>::operator=(std::move(t_node));
        }

        return *this;
    }

  public:
    std::uint8_t m_key;
    std::size_t m_height = defines::DEFAULT_HEIGHT;
};

template <typename T> class AVLTree : public BSTree<T> {
  public:
    using node = AVLNode<T>;
  public:
    constexpr AVLTree() noexcept : BSTree<T>() {}

    constexpr AVLTree(const std::initializer_list<T>& t_list) : BSTree<T>(t_list) {}

    template <typename U,
              typename = std::enable_if_t<std::is_base_of_v<BSTree<T>, std::remove_reference_t<U>>>>
    explicit AVLTree(U&& t_tree) : BSTree<T>(std::forward<U>(t_tree)) {}

    virtual ~AVLTree() {}

  public:
    AVLTree<T>& operator=(const AVLTree<T>& t_tree) {
        if (this != &t_tree) {
            BSTree<T>::operator=(t_tree);
        }

        return *this;
    }

    AVLTree<T>& operator=(AVLTree<T>&& t_tree) noexcept {
        if (this != &t_tree) {
            BSTree<T>::operator=(std::move(t_tree));
        }

        return *this;
    }

  public:
    [[nodiscard]] virtual const node* const get_root() const noexcept override { return m_root; }

    [[nodiscard]] virtual node* get_root() noexcept override { return m_root; }
  protected:
    node* m_root = nullptr;
};

} // namespace own

#endif
