/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
  public:
    ObjectExp(const Location& location, ast::NameTy* type_name);

    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    ~ObjectExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const ast::NameTy& obj_get() const;
    ast::NameTy& obj_get();

  protected:
    ast::NameTy* obj_;
  };
} // namespace ast
#include <ast/object-exp.hxx>
