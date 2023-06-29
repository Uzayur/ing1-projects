/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const ast::exps_type& SeqExp::exp_get() const { return *exp_; }
  inline ast::exps_type& SeqExp::exp_get() { return *exp_; }
} // namespace ast
