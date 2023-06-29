/**
 ** \file ast/object-exp.cc
 ** \brief Implementation of ast::ObjectExp.
 */

#include <ast/object-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  ObjectExp::ObjectExp(const Location& location, ast::NameTy* type_name)
    : Exp(location)
    , obj_(type_name)
  {}

  ObjectExp::~ObjectExp() { delete obj_; }

  void ObjectExp::accept(ConstVisitor& v) const { v(*this); }

  void ObjectExp::accept(Visitor& v) { v(*this); }

} // namespace ast
