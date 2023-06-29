/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{

  EscapesVisitor::EscapesVisitor()
    : super_type()
  {}

  void EscapesVisitor::operator()(ast::SimpleVar& e)
  {
    auto dept_e = map_dec_.find(e.def_get());
    if (dept_e->second < dept_)
      e.def_get()->escapable_set(true);
    super_type::operator()(e);
  }

  void EscapesVisitor::operator()(ast::VarDec& e)
  {
    e.escapable_set(false);
    map_dec_[&e] = dept_;
    super_type::operator()(e);
  }

  void EscapesVisitor::operator()(ast::FunctionDec& e)
  {
    dept_++;
    super_type::operator()(e);
    dept_--;
  }

} // namespace escapes
