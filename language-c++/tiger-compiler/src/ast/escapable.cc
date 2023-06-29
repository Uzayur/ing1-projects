/**
 ** \file ast/escapable.cc
 ** \brief Implementation of ast::Escapable.
 */

#include <ast/escapable.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  Escapable::Escapable(bool escapable)
    : escapable_(escapable)
  {}

} // namespace ast
