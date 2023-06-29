/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// CallExp.
  class CallExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    CallExp(const Location& location, misc::symbol name, ast::exps_type* args);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;
    ~CallExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const misc::symbol symbol_get() const;
    misc::symbol symbol_get();

    const ast::exps_type& arg_get() const;
    ast::exps_type& arg_get();

    void def_set(FunctionDec* fdec);

    FunctionDec* def_get();
    const FunctionDec* def_get() const;

    misc::symbol name_get() const;
    void name_set(misc::symbol);

  protected:
    misc::symbol symbol_;
    ast::exps_type* arg_;
    FunctionDec* def_ = nullptr;
  };
} // namespace ast
#include <ast/call-exp.hxx>
