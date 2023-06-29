/**
 ** \file ast/typable.cc
 ** \brief Implementation of ast::Typable.
 */

#include <ast/typable.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.

  void Typable::type_set(const type::Type* type) { this->self_type = type; }

  const type::Type* Typable::type_get() const { return this->self_type; }
} // namespace ast
