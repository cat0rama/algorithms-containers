#ifndef AVLNODE_HPP_
#define AVLNODE_HPP_

#include <utility>

#include "ITree.hpp"

namespace own {
template <typename T> struct AVLNode : public INode {
    constexpr AVLNode() noexcept {}

    template <typename TT,
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit AVLNode(TT&& t_val) : m_key(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr AVLNode(TT&& t_val, AVLNode* t_left, AVLNode* t_right)
        : AVLNode(std::forward<TT>(t_val)), m_left(t_left), m_right(t_right) {}

    constexpr AVLNode(AVLNode&& t_node) noexcept {
        *this = std::move(t_node);
    }

    virtual ~AVLNode() = default;

  public:
    AVLNode& operator=(AVLNode<T>&& t_node) noexcept {
        static_assert(std::is_move_assignable_v<T> || std::is_move_constructible_v<T>,
                      "object cannot be moved.\n");

        if (this != &t_node) {
            m_val = std::exchange(t_node.m_val, T());
            m_left = std::exchange(t_node.m_left, nullptr);
            m_right = std::exchange(t_node.m_right, nullptr);
        }

        return *this;
    }

  public:
    T m_key = T();
    AVLNode* m_left = nullptr;
    AVLNode* m_right = nullptr;
    AVLNode* m_parent = nullptr;

  public:
    std::size_t m_height = defines::DEFAULT_HEIGHT;
};
} // namespace own

#endif