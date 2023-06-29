#pragma once

#include <memory>

#include "tree.hh"

namespace tree
{
    class Node : public Tree
    {
    public:
        Node(const std::string& value, std::shared_ptr<Tree> lhs,
             std::shared_ptr<Tree> rhs);
        ~Node();
        void accept(visitor::Visitor& v) const override;

        std::shared_ptr<const Tree> lhs_get() const;
        void lhs_set(std::shared_ptr<const Tree> t);
        std::shared_ptr<const Tree> rhs_get() const;
        void rhs_set(std::shared_ptr<const Tree> t);

    private:
        std::shared_ptr<const Tree> lhs_;
        std::shared_ptr<const Tree> rhs_;
    };
} // namespace tree

#include "node.hxx"
