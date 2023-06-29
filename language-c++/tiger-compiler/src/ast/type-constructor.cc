/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/type-constructor.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.

  void TypeConstructor::create_type_set(const type::Type* type)
  {
    this->new_type = type;
  }

  const type::Type* TypeConstructor::created_type_get() const
  {
    return this->new_type;
  }

} // namespace ast
