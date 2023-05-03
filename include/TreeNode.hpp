#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include "ITree.hpp"

// подумать насчет операторов сравнения

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

    virtual ~TreeNode() = default;

    // protected чтобы нельзя было создавать производный обьект через ссылку на базовый класс
  protected:
    TreeNode& operator=(TreeNode<T>&& t_node) noexcept {
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
}

#endif