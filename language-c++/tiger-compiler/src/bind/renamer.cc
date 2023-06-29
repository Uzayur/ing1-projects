/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include "renamer.hh"
#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  Renamer::Renamer() {}

  // FIXME: Some code was deleted here.
  void Renamer::operator()(ast::NameTy& e)
  {
    Renamer::visit(e, e.def_get());
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::CallExp& e)
  {
    Renamer::visit(e, e.def_get());
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::SimpleVar& e)
  {
    Renamer::visit(e, e.def_get());
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::FunctionDec& e)
  {
    if (e.body_get() != nullptr && e.name_get() != "_main")
      {
        Renamer::visit(e, &e);
        super_type::operator()(e);
      }
    else
      {
        //ajouter les primitives dans la map
        new_names_.insert(std::pair<const ast::Dec*, misc::symbol>(
                    static_cast<const ast::Dec*>(&e), e.name_get()));
        super_type::operator()(e);
      }
  }

  void Renamer::operator()(ast::VarDec& e)
  {
    Renamer::visit(e, &e);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::TypeDec& e)
  {
    Renamer::visit(e, &e);
    super_type::operator()(e);
  }

} // namespace bind
