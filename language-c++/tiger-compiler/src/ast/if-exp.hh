/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
  public:
    IfExp(const Location& location, Exp* test, Exp* thenclause);
    IfExp(const Location& location,
          Exp* test,
          Exp* thenclause,
          Exp* elseclause);

    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;
    ~IfExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const Exp& test_get() const;
    Exp& test_get();

    const Exp& thenclause_get() const;
    Exp& thenclause_get();

    const Exp& elseclause_get() const;
    Exp& elseclause_get();

  protected:
    Exp* test_;
    Exp* thenclause_;
    Exp* elseclause_ = nullptr;
  };
} // namespace ast
#include <ast/if-exp.hxx>
