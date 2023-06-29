#include <cassert>
#include <iostream>

#include "unordered-multimap.hh"

int main()
{
    UnorderedMultimap<int, int> m;
    assert(m.empty());
    assert(m.size() == 0);

    m.add(42, 20);
    m.add(42, 21);

    m.add(1337, 1);

    std::cout << "number of elems with key 42: " << m.count(42) << '\n';
    std::cout << "total number of elems: " << m.size() << '\n';

    std::cout << "elems with key 42:" << '\n';
    auto range = m.equal_range(42);
    for (auto it = range.first; it != range.second; ++it)
    {
        std::cout << it->second << '\n';
    }
}
