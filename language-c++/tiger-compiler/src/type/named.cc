/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
    , type_(type)
  {}

  // FIXME: Some code was deleted here (Inherited functions).
  void Named::accept(ConstVisitor& v) const { v(*this); }

  void Named::accept(Visitor& v) { v(*this); }

  // FIXME: Some code was deleted here (Sound).
  bool Named::sound() const
  {
    auto rec = std::set<const Type*>();
    auto last = this;

    while (last)
      {
        if (!rec.contains(last))
          rec.insert(last);
        else
          return false;
        last = dynamic_cast<const Named*>(last->type_get());
      }
    return true;
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).
  bool Named::compatible_with(const Type& other) const
  {
    return this->type_get()->compatible_with(other);
  }

} // namespace type
