/**
 ** \file ast/break-exp.hh
 ** \brief Declaration of ast::BreakExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// BreakExp.
  class BreakExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    explicit BreakExp(const Location& location);
    BreakExp(const BreakExp&) = delete;
    BreakExp& operator=(const BreakExp&) = delete;

    void def_set(Exp* exp);

    Exp* def_get();
    const Exp* def_get() const;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

  private:
    Exp* def_ = nullptr;
  };
} // namespace ast
#include <ast/break-exp.hxx>
