#pragma once

namespace tree
{
    class Tree;
    class Node;
    class Leaf;
} // namespace tree

namespace visitor
{
    class Visitor
    {
    public:
        virtual void visit(const tree::Tree& e);
        virtual void visit(const tree::Node& e) = 0;
        virtual void visit(const tree::Leaf& e) = 0;
    };
} // namespace visitor

#include "visitor.hxx"
