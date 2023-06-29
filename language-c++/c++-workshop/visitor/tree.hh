#pragma once

#include <string>

namespace visitor
{
    class Visitor;
}

namespace tree
{
    class Tree
    {
    public:
        Tree(const std::string& value);
        virtual ~Tree() = default;
        virtual void accept(visitor::Visitor& v) const = 0;

        const std::string& value_get() const;
        void value_set(const std::string& value);

    private:
        std::string value_;
    };
} // namespace tree

#include "tree.hxx"
