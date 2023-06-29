#pragma once

#include "tree.hh"

namespace tree
{
    class Leaf : public Tree
    {
    public:
        Leaf(const std::string& value);
        void accept(visitor::Visitor& v) const override;
    };
} // namespace tree
