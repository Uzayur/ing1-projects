/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const ast::NameTy& RecordExp::name_get() const { return *name_; }
  inline ast::NameTy& RecordExp::name_get() { return *name_; }

  inline const ast::fieldinits_type& RecordExp::field_get() const
  {
    return *field_;
  }
  inline ast::fieldinits_type& RecordExp::field_get() { return *field_; }
} // namespace ast
