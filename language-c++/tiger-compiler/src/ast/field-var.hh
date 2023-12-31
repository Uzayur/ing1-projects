/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// FieldVar.
  class FieldVar : public Var
  {
  public:
    FieldVar(const Location& location, Var* var, misc::symbol name);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;
    ~FieldVar() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const Var& var_get() const;
    Var& var_get();
    const misc::symbol name_get() const;
    misc::symbol name_get();

  protected:
    Var* var_;
    misc::symbol name_;
  };
} // namespace ast
#include <ast/field-var.hxx>
