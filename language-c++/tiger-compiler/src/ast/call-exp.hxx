/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const misc::symbol CallExp::symbol_get() const { return symbol_; }
  inline misc::symbol CallExp::symbol_get() { return symbol_; }

  inline const ast::exps_type& CallExp::arg_get() const { return *arg_; }
  inline ast::exps_type& CallExp::arg_get() { return *arg_; }

  inline void CallExp::def_set(FunctionDec* fdec) { def_ = fdec; }

  inline FunctionDec* CallExp::def_get() { return def_; }
  inline const FunctionDec* CallExp::def_get() const { return def_; }

  inline misc::symbol CallExp::name_get() const { return symbol_; }
  inline void CallExp::name_set(misc::symbol name) { symbol_ = name; }
} // namespace ast
