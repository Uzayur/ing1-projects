#pragma once

#include <map>

template <typename T1, typename T2>
class Bimap
{
    using iteratorT1 = typename std::map<T1, T2>::iterator;
    using iteratorT2 = typename std::map<T2, T1>::iterator;

public:
    void insert(const T1& v1, const T2& v2);
    void insert(const T2& v1, const T1& v2);

    void erase(const T1& v);
    void erase(const T2& v);

    iteratorT1 find(const T1& v);
    iteratorT2 find(const T2& v);

    std::size_t size() const;
    void clear();

    std::map<T1, T2> lhs;
    std::map<T2, T1> rhs;
};

#include "bimap.hxx"
