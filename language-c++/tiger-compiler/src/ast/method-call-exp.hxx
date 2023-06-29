/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const ast::Var& MethodCallExp::obj_get() const { return *obj_; }
  inline ast::Var& MethodCallExp::obj_get() { return *obj_; }
} // namespace ast
