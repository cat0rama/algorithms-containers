#ifndef ITREE_HPP_H
#define ITREE_HPP_H

#include "traits.hpp"

namespace own {
struct INode {
    INode() noexcept = default;
    INode(const INode&) = delete;
    virtual ~INode() = default;
};
} // namespace own

#endif
