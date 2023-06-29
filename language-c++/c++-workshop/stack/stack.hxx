#include "stack-creation-failed.hh"
#include "stack-empty.hh"
#include "stack-max-size.hh"
#include "stack.hh"

template <class T>
Stack<T>& Stack<T>::push(const T& item)
{
    if (vec_.size() == max_size_)
        throw StackMaxSize();

    vec_.push_back(item);
    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator+=(const T& elt)
{
    return this->push(elt);
}

template <class T>
Stack<T>& Stack<T>::operator<<(const T& elt)
{
    return this->push(elt);
}

template <class T>
T Stack<T>::pop()
{
    if (vec_.empty())
        throw StackEmpty();

    auto save = vec_.back();
    vec_.pop_back();
    return save;
}

template <class T>
T Stack<T>::operator--()
{
    return this->pop();
}

template <class T>
T Stack<T>::operator[](size_t i)
{
    if (i >= vec_.size())
        throw std::out_of_range("Out of range.");

    return vec_[vec_.size() - i - 1];
}

template <class T>
bool Stack<T>::operator==(Stack<T> stack)
{
    if (this->max_size() != stack.max_size_
        || this->vec_.size() != stack.vec_.size())
        return false;

    for (size_t k = 0; k < this->vec_.size(); k++)
    {
        if (this->vec_[k] != stack.vec_[k])
            return false;
    }
    return true;
}

template <class T>
std::ostream& Stack<T>::print(std::ostream& s) const
{
    auto size = vec_.size() - 1;

    for (size_t k = 0; k < size; k++)
        s << vec_[k] << ' ';

    s << vec_[size];
    return s;
}

template <class T>
typename Stack<T>::const_iterator Stack<T>::begin() const
{
    return vec_.rbegin();
}

template <class T>
typename Stack<T>::iterator Stack<T>::begin()
{
    return vec_.rbegin();
}

template <class T>
typename Stack<T>::const_iterator Stack<T>::end() const
{
    return vec_.rend();
}

template <class T>
typename Stack<T>::iterator Stack<T>::end()
{
    return vec_.rend();
}

template <class T>
void Stack<T>::resize(size_t t)
{
    try
    {
        while (vec_.size() > t)
            vec_.pop_back();

        max_size_ = t;
        vec_.reserve(max_size_);
    }
    catch (std::length_error& e)
    {
        throw StackCreationFailed("Max stack size is too big.");
    }
    catch (std::bad_alloc& e)
    {
        throw StackCreationFailed("Allocation failed.");
    }
}

template <class T>
size_t Stack<T>::max_size() const
{
    return max_size_;
}

template <class T>
std::ostream& operator<<(std::ostream& ost, const Stack<T>& p)
{
    return p.print(ost);
}
