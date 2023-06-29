/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type
{
  void Record::accept(ConstVisitor& v) const { v(*this); }

  void Record::accept(Visitor& v) { v(*this); }

  // FIXME: Some code was deleted here (Field manipulators).
  int Record::field_index(misc::symbol key) const
  {
    int index = 0;
    for (auto var : fields_)
      {
        if (var.name_get() == key)
          return index;
        index++;
      }
    return -1;
  }

  const Type* Record::field_type(misc::symbol key) const
  {
    for (auto var : fields_)
      {
        if (var.name_get() == key)
          return &var.type_get();
      }
    return nullptr;
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Record).
  bool Record::compatible_with(const Type& other) const
  {
      auto cast_nil = dynamic_cast<const type::Nil*>(&other);
      if (cast_nil != nullptr)
          return true;

      if (other.actual() == this->actual())
          return true;

      return false;
  }
} // namespace type
