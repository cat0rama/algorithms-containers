#ifndef ITREE_HPP_H
#define ITREE_HPP_H

#include "defines.hpp"
#include "traits.hpp"

// Абстрактный класс ноды для построения иерархии

namespace own {
struct INode {
    INode() noexcept = default;
    INode(const INode&) = delete;
    virtual ~INode() = default;
    INode& operator=(const INode&) = delete;
};
} // namespace own

#endif
