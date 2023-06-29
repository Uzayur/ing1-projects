#include "int-container.hh"

MyIntContainer::MyIntContainer(size_t size)
    : current_size_(0)
    , max_size_(size)
    , elems_(new int[size])
{}

void MyIntContainer::print() const
{
    int test = 0;
    for (size_t k = 0; k < current_size_; k++)
    {
        if (test == 0)
        {
            std::cout << elems_[k];
            test = 1;
        }
        else
            std::cout << " | " << elems_[k];
    }
    if (test == 1)
        std::cout << "\n";
}

size_t MyIntContainer::get_len() const
{
    return current_size_;
}

bool MyIntContainer::add(int elem)
{
    if (current_size_ == max_size_)
        return false;

    elems_[current_size_] = elem;
    current_size_++;

    return true;
}

std::optional<int> MyIntContainer::pop()
{
    if (current_size_ == 0)
        return std::nullopt;

    int last_elem = elems_[current_size_ - 1];
    current_size_ -= 1;

    return last_elem;
}

std::optional<int> MyIntContainer::get(size_t position) const
{
    if (position >= current_size_)
        return std::nullopt;
    return elems_[position];
}

std::optional<size_t> MyIntContainer::find(int elem) const
{
    for (size_t k = 0; k < current_size_; k++)
    {
        if (elems_[k] == elem)
            return k;
    }
    return std::nullopt;
}

void MyIntContainer::sort()
{
    for (size_t rep = 0; rep < current_size_; rep++)
    {
        for (size_t index = 0; index < current_size_ - 1; index++)
        {
            if (elems_[index] > elems_[index + 1])
            {
                int tmp = elems_[index];
                elems_[index] = elems_[index + 1];
                elems_[index + 1] = tmp;
            }
        }
    }
}

bool MyIntContainer::is_sorted() const
{
    if (current_size_ == 0)
        return true;

    for (size_t index = 0; index < current_size_ - 1; index++)
    {
        if (elems_[index] > elems_[index + 1])
            return false;
    }
    return true;
}
