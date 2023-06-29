#include "list.hh"

List::List()
    : nb_elts_(0)
    , first_(nullptr)
    , last_(nullptr)
{}

void List::push_front(int i)
{
    auto node = std::make_shared<Node>(i);

    if (nb_elts_ == 0)
        last_ = node;

    else
    {
        first_->prev_set(node);
        node->next_set(first_);
    }

    first_ = node;
    nb_elts_ += 1;
}

void List::push_back(int i)
{
    auto node = std::make_shared<Node>(i);

    if (nb_elts_ == 0)
        first_ = node;
    else
    {
        last_->next_set(node);
        node->prev_set(last_);
    }

    last_ = node;
    nb_elts_ += 1;
}

std::optional<int> List::pop_front()
{
    if (nb_elts_ == 0)
        return std::nullopt;

    auto elt = first_->val_get();

    first_ = first_->next_get();
    if (!first_)
        last_ = nullptr;

    else
        first_->prev_set(nullptr);

    nb_elts_ -= 1;
    return elt;
}

std::optional<int> List::pop_back()
{
    if (nb_elts_ == 0)
        return std::nullopt;

    auto elt = last_->val_get();
    last_ = last_->prev_get();

    if (!last_)
        first_ = nullptr;

    else
        last_->next_set(nullptr);

    nb_elts_ -= 1;
    return elt;
}

void List::print(std::ostream& os) const
{
    auto node = first_;

    if (!first_)
        return;

    while (node != last_)
    {
        os << node->val_get() << ' ';
        node = node->next_get();
    }

    os << node->val_get();
}

int List::length() const
{
    return nb_elts_;
}
