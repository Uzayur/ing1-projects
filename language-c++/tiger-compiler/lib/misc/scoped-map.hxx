/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include <range/v3/view/reverse.hpp>

namespace misc
{
  // FIXME: Some code was deleted here.
  template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
    this->stack.back().insert_or_assign(key, value);
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const
  {
    auto search = this->stack.back().find(key);
    if (search != this->stack.back().end())
      return search->second;
    else
      throw std::range_error("undifined variable.");
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_begin()
  {
    if (this->stack.empty())
      this->stack.push_back(std::map<Key, Data>());
    else
      this->stack.push_back(this->stack.back());
  }

  template <typename Key, typename Data> void scoped_map<Key, Data>::scope_end()
  {
    this->stack.pop_back();
  }

  template <typename Key, typename Data>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

  template <typename Key, typename Data>
  std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
    for (auto elem : this->stack)
      {
        ostr << elem.second << " | ";
      }

    ostr << "\n";
    return ostr;
  }
} // namespace misc
