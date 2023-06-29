/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline bool Escapable::escapable_get() const { return escapable_; }
  inline void Escapable::escapable_set(bool setter) { escapable_ = setter; }
} // namespace ast
