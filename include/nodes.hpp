#ifndef NODES_HPP_
#define NODES_HPP_

#include <cstdint>
#include <memory>
#include <utility>

namespace own {

struct ITree {
    ITree() noexcept = default;
    ITree(const ITree&) = delete;
    ITree& operator=(ITree&&) = delete;
    virtual ~ITree() = default;
};

template <typename T> struct TreeNode : public ITree {
    TreeNode() noexcept : m_val(T()), m_left(nullptr), m_right(nullptr) {}

    template <typename TT, // диспатчу универсальную ссылку чтобы случайно не вызывался move ctor
              typename = std::enable_if_t<!std::is_base_of_v<ITree, std::remove_reference_t<TT>>>>
    constexpr explicit TreeNode(TT&& t_val) : m_val(std::forward<TT>(t_val)) {}

    template <typename TT>
    constexpr TreeNode(TT&& t_val, TreeNode* t_left, TreeNode* t_right)
        : m_val(std::forward<TT>(t_val)), m_left(t_left), m_right(t_right) {}

    constexpr TreeNode(TreeNode&& t_node) noexcept {
        static_assert(std::is_move_assignable_v<decltype(t_node.m_val)>,
                      "object cannot be moved.\n");
        m_val = std::exchange(t_node.m_val, T());
        m_left = std::exchange(t_node.m_left, nullptr);
        m_right = std::exchange(t_node.m_right, nullptr);
    }

    TreeNode& operator=(TreeNode&&) = delete;

  public:
    T m_val;
    TreeNode* m_left;
    TreeNode* m_right;
};

template <typename T> struct AVLNode : protected TreeNode<T> {
    AVLNode() noexcept : TreeNode<T>() {}

    template <typename TT,
              typename = std::enable_if_t<!std::is_base_of_v<ITree, std::remove_reference_t<TT>>>>
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

} // namespace own

#endif
