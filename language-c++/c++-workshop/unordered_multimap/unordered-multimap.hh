#pragma once

#include <utility>
#include <vector>

template <typename KeyType, typename ValueType>
class UnorderedMultimap
{
    using iterator =
        typename std::vector<std::pair<KeyType, ValueType>>::iterator;

public:
    bool empty() const;
    unsigned size() const;
    std::pair<iterator, iterator> equal_range(const KeyType& key);
    void add(const KeyType& key, const ValueType& value);
    unsigned count(const KeyType& key) const;
    void clear();

private:
    std::vector<std::pair<KeyType, ValueType>> map_;
};

#include "unordered-multimap.hxx"
