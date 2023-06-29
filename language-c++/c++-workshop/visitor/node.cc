#include "node.hh"

#include "visitor.hh"

namespace tree
{
    Node::Node(const std::string& value, std::shared_ptr<Tree> lhs,
               std::shared_ptr<Tree> rhs)
        : Tree(value)
        , lhs_(lhs)
        , rhs_(rhs)
    {}

    Node::~Node()
    {}

    void Node::accept(visitor::Visitor& v) const
    {
        v.visit(*this);
    }
} // namespace tree
