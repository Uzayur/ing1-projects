/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    SeqExp(const Location& location, ast::exps_type* exps);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;
    ~SeqExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const ast::exps_type& exp_get() const;
    ast::exps_type& exp_get();

  protected:
    ast::exps_type* exp_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
