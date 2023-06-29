#pragma once

#include "tree.hh"

namespace tree
{
    inline const std::string& Tree::value_get() const
    {
        return value_;
    }

    inline void Tree::value_set(const std::string& s)
    {
        value_ = s;
    }
} // namespace tree
