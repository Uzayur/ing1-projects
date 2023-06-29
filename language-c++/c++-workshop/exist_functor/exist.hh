#pragma once

template <class T>
class Exist
{
public:
    bool operator()(T elt);

private:
    std::vector<T> vec_;
};

#include "exist.hxx"
