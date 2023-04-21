#ifndef AVLNODE_HPP_
#define AVLNODE_HPP_

#include <utility>

#include "TreeNode.hpp"

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
}

#endif