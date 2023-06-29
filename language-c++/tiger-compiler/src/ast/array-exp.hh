/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    ArrayExp(const Location& location,
             ast::NameTy* type_name,
             ast::Exp* size,
             ast::Exp* init);

    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    ~ArrayExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const ast::NameTy& obj_get() const;
    ast::NameTy& obj_get();

    const Exp& size_get() const;
    Exp& size_get();

    const Exp& init_get() const;
    Exp& init_get();

  protected:
    ast::NameTy* obj_;
    Exp* size_;
    Exp* init_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
