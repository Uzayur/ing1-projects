#include "bimap.hh"

template <typename T1, typename T2>
void Bimap<T1, T2>::insert(const T1& v1, const T2& v2)
{
    lhs.insert({ v1, v2 });
    rhs.insert({ v2, v1 });
}

template <typename T1, typename T2>
void Bimap<T1, T2>::insert(const T2& v1, const T1& v2)
{
    rhs.insert({ v1, v2 });
    lhs.insert({ v2, v1 });
}

template <typename T1, typename T2>
void Bimap<T1, T2>::erase(const T1& v)
{
    for (auto elt : rhs)
    {
        if (elt.second == v)
        {
            rhs.erase(elt.first);
            break;
        }
    }
    lhs.erase(v);
}

template <typename T1, typename T2>
void Bimap<T1, T2>::erase(const T2& v)
{
    for (auto elt : lhs)
    {
        if (elt.second == v)
        {
            lhs.erase(elt.first);
            break;
        }
    }
    rhs.erase(v);
}

template <typename T1, typename T2>
typename Bimap<T1, T2>::iteratorT1 Bimap<T1, T2>::find(const T1& v)
{
    return lhs.find(v);
}

template <typename T1, typename T2>
typename Bimap<T1, T2>::iteratorT2 Bimap<T1, T2>::find(const T2& v)
{
    return rhs.find(v);
}

template <typename T1, typename T2>
std::size_t Bimap<T1, T2>::size() const
{
    return lhs.size();
}

template <typename T1, typename T2>
void Bimap<T1, T2>::clear()
{
    lhs.clear();
    rhs.clear();
}
