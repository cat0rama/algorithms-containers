#ifndef ITREE_HPP_H
#define ITREE_HPP_H

#include "defines.hpp"
#include "AVLNode.hpp"

// абстрактный класс ноды для построения иерархии

namespace own {
struct INode {
    INode() noexcept = default;
    INode(const INode&) = delete;
    virtual ~INode() = default;
    INode& operator=(const INode&) = delete;
};

// подумать как можно сделать лучше, слишком много проблем возникает при данном подходе
template <typename L, typename U = AVLNode<L>> struct NodeWrapper {
    U* m_node = nullptr;
    using value = U;
};
} // namespace own

#endif
