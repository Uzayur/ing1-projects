/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/object-visitor.hh>
#include <misc/contract.hh>

namespace ast
{
  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}

  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
  {
    // FIXME: Some code was deleted here.
    e.super_get().accept(*this);
    e.chunks_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodChunk>& e)
  {
    // FIXME: Some code was deleted here.
    for (const auto chunk : e.decs_get())
      chunk->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
    // FIXME
    e.formals_get().accept(*this);
    if (e.result_get())
      e.result_get()->accept(*this);
    e.body_get()->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
    // FIXME: Some code was deleted here.
    for (const auto k : e.arg_get())
      k->accept(*this);
    e.obj_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
    // FIXME: Some code was deleted here.
    e.obj_get().accept(*this);
  }

} // namespace ast
