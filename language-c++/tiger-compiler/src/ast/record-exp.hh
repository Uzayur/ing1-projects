/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    RecordExp(const Location& location,
              ast::NameTy* type_name,
              ast::fieldinits_type* fields);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;
    ~RecordExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const ast::NameTy& name_get() const;
    ast::NameTy& name_get();

    const ast::fieldinits_type& field_get() const;
    ast::fieldinits_type& field_get();

  protected:
    ast::NameTy* name_;
    ast::fieldinits_type* field_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
