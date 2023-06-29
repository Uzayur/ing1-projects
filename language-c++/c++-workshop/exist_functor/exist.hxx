#include "exist.hh"

template <class T>
bool Exist<T>::operator()(T elt)
{
    for (auto element : vec_)
    {
        if (element == elt)
            return true;
    }

    vec_.push_back(elt);
    return false;
}
