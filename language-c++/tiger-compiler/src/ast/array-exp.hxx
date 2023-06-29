/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const ast::NameTy& ArrayExp::obj_get() const { return *obj_; }
  inline ast::NameTy& ArrayExp::obj_get() { return *obj_; }

  inline const Exp& ArrayExp::size_get() const { return *size_; }
  inline Exp& ArrayExp::size_get() { return *size_; }

  inline const Exp& ArrayExp::init_get() const { return *init_; }
  inline Exp& ArrayExp::init_get() { return *init_; }

} // namespace ast
