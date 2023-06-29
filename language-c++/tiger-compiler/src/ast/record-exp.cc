/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <ast/record-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  RecordExp::RecordExp(const Location& location,
                       ast::NameTy* type_name,
                       ast::fieldinits_type* fields)
    : Exp(location)
    , name_(type_name)
    , field_(fields)
  {}

  RecordExp::~RecordExp()
  {
    delete name_;
    delete field_;
  }

  void RecordExp::accept(ConstVisitor& v) const { v(*this); }

  void RecordExp::accept(Visitor& v) { v(*this); }

} // namespace ast
