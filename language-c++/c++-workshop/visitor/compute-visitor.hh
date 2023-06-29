#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "leaf.hh"
#include "node.hh"
#include "visitor.hh"

namespace visitor
{
    class ComputeVisitor : public Visitor
    {
    public:
        void visit(const tree::Tree& e) override;
        void visit(const tree::Node& e) override;
        void visit(const tree::Leaf& e) override;

        int value_get()
        {
            return n_;
        }

    private:
        int n_;
    };
} // namespace visitor
