#include "unordered-multimap.hh"

template <typename KeyType, typename ValueType>
bool UnorderedMultimap<KeyType, ValueType>::empty() const
{
    return map_.empty();
}

template <typename KeyType, typename ValueType>
unsigned UnorderedMultimap<KeyType, ValueType>::size() const
{
    return map_.size();
}

template <typename KeyType, typename ValueType>
std::pair<typename UnorderedMultimap<KeyType, ValueType>::iterator,
          typename UnorderedMultimap<KeyType, ValueType>::iterator>
UnorderedMultimap<KeyType, ValueType>::equal_range(const KeyType& key)
{
    auto new_map = new std::vector<std::pair<KeyType, ValueType>>();

    for (auto& pair : map_)
    {
        if (std::get<0>(pair) == key)
            new_map->push_back(pair);
    }

    auto begin = new_map->begin();
    auto end = new_map->end();

    auto range = std::make_pair<>(begin, end);

    return range;
}

template <typename KeyType, typename ValueType>
void UnorderedMultimap<KeyType, ValueType>::add(const KeyType& key,
                                                const ValueType& value)
{
    auto pair = std::make_pair(key, value);
    map_.push_back(pair);
}

template <typename KeyType, typename ValueType>
unsigned UnorderedMultimap<KeyType, ValueType>::count(const KeyType& key) const
{
    int count = 0;
    for (auto& pair : map_)
    {
        if (std::get<0>(pair) == key)
            count++;
    }
    return count;
}

template <typename KeyType, typename ValueType>
void UnorderedMultimap<KeyType, ValueType>::clear()
{
    map_.clear();
}
