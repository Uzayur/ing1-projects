#pragma once

#include "tree.hh"
#include "visitor.hh"

namespace visitor
{
    inline void Visitor::visit(const tree::Tree& e)
    {
        e.accept(*this);
    }
} // namespace visitor
