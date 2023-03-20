#ifndef AVLTREE_HPP_H
#define AVLTREE_HPP_H

#include "BSTree.hpp"

namespace own {
template <typename T> struct AVLNode : protected TreeNode<T> {
    AVLNode() noexcept : TreeNode<T>() {}

    template <typename TT,
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit AVLNode(TT&& t_val) : TreeNode<T>(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr AVLNode(TT&& t_val, AVLNode* t_left, AVLNode* t_right)
        : TreeNode<T>(std::forward<TT>(t_val), t_left, t_right) {}

    constexpr AVLNode(AVLNode&& t_node) noexcept : TreeNode<T>(std::move(t_node)) {
        m_height = std::exchange(t_node.m_height, 0);
    }

    AVLNode& operator=(AVLNode&&) = delete;

  public:
    std::uint8_t m_height = 1;
};

template <typename T>
class AVLTree : public BSTree<T> {
public:
    AVLTree() noexcept : BSTree<T> () {}

    template <typename U> AVLTree(U&& t_val): BSTree<T> (std::forward<U>(t_val)){}
public:

};

}


#endif
