/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const ast::NameTy& ObjectExp::obj_get() const { return *obj_; }
  inline ast::NameTy& ObjectExp::obj_get() { return *obj_; }

} // namespace ast
