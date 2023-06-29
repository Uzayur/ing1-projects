#pragma once

#include "node.hh"

namespace tree
{
    inline std::shared_ptr<const Tree> Node::lhs_get() const
    {
        return lhs_;
    }

    inline void Node::lhs_set(std::shared_ptr<const Tree> t)
    {
        lhs_ = t;
    }

    inline std::shared_ptr<const Tree> Node::rhs_get() const
    {
        return rhs_;
    }

    inline void Node::rhs_set(std::shared_ptr<const Tree> t)
    {
        rhs_ = t;
    }
} // namespace tree
