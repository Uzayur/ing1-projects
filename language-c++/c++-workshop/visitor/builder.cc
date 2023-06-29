#include "builder.hh"

#include "leaf.hh"
#include "node.hh"

Builder::Builder(const std::string& name)
    : in_{ name }
{}

std::shared_ptr<tree::Tree> Builder::create_leaf(int c, bool neg)
{
    auto i = 0;

    if (c >= '0' && c <= '9')
    {
        int num = c - '0';
        while ((i = in_.get()) >= '0' && i <= '9')
            num = num * 10 + i - '0';

        if (neg)
            num = -num;
        return std::make_shared<tree::Leaf>(std::to_string(num));
    }
    return nullptr;
}

std::shared_ptr<tree::Tree> Builder::build()
{
    int c = 0;

    while ((c = in_.get()) == ' ')
        continue;

    switch (c)
    {
    case '-': {
        auto tmp = in_.get();
        if (tmp >= '0' && tmp <= '9')
            return create_leaf(tmp, true);
        return create_node("-");
    }

    case '+':
        return create_node("+");
    case '*':
        return create_node("*");
    case '/':
        return create_node("/");

    default:
        auto n = create_leaf(c, false);
        if (!n)
            throw std::domain_error("parse error");
        return n;
    }
}

std::shared_ptr<tree::Tree> Builder::create_node(const std::string& op)
{
    auto left = build();
    auto right = build();
    return std::make_shared<tree::Node>(op, left, right);
}
