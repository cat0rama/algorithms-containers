#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include "ITree.hpp"

// подумать насчет операторов сравнения

namespace own {
template <typename T> struct TreeNode : public INode {
    constexpr TreeNode() noexcept {}
     
    template <typename TT, /* диспатчу forward reference чтобы TT не выигрывал перегрузку 
        во всех случаях, так как это может приводить к ошибкам
        (например может перекрыть конструктор перемещения) (https://godbolt.org/z/Efvj1eb1G) */
              typename = std::enable_if_t<!std::is_base_of_v<INode, std::remove_reference_t<TT>>>>
    constexpr explicit TreeNode(TT&& t_val)
        : m_val(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr TreeNode(TT&& t_val, TreeNode* t_left, TreeNode* t_right, TreeNode* t_parent = nullptr)
        : TreeNode(std::forward<TT>(t_val)), m_left(t_left), m_right(t_right), m_parent(t_parent) {}

    constexpr TreeNode(TreeNode&& t_node) noexcept { *this = std::move(t_node); }

    virtual ~TreeNode() = default;

  public:
    TreeNode& operator=(TreeNode<T>&& t_node) noexcept {
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
    T m_val = T();
    TreeNode* m_left = nullptr;
    TreeNode* m_right = nullptr;
    TreeNode* m_parent = nullptr;
};
} // namespace own

#endif