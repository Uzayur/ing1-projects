#include "compute-visitor.hh"

namespace visitor
{
    void ComputeVisitor::visit(const tree::Leaf& e)
    {
        n_ = std::stoi(e.value_get());
    }

    void ComputeVisitor::visit(const tree::Node& e)
    {
        e.lhs_get()->accept(*this);
        int lhs = n_;

        e.rhs_get()->accept(*this);
        int rhs = n_;

        auto op = e.value_get();

        if (op == "+")
            n_ = lhs + rhs;

        else if (op == "-")
            n_ = lhs - rhs;

        else if (op == "*")
            n_ = lhs * rhs;

        else if (op == "/")
        {
            if (rhs == 0)
                throw std::overflow_error("Divide by zero exception");
            n_ = lhs / rhs;
        }
    }

    void ComputeVisitor::visit(const tree::Tree& e)
    {
        e.accept(*this);
    }
} // namespace visitor
