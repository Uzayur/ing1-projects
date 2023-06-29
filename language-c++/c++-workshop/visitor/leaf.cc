#include "leaf.hh"

#include "visitor.hh"

namespace tree
{
    Leaf::Leaf(const std::string& value)
        : Tree(value)
    {}

    void Leaf::accept(visitor::Visitor& v) const
    {
        v.visit(*this);
    }
} // namespace tree
