/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>
#include "renamer.hh"

namespace bind
{
  // FIXME: Some code was deleted here.
  template <typename Def> misc::symbol Renamer::new_name_compute(const Def& e)
  {
    misc::symbol new_symbol = misc::symbol::fresh(e->name_get());
    new_names_.insert(std::pair<const ast::Dec*, misc::symbol>(
      static_cast<const ast::Dec*>(e), new_symbol));
    return new_symbol;
  }

  template <typename Def> misc::symbol Renamer::new_name(const Def& e)
  {
    if (new_names_.find(e) != new_names_.end())
      {
        return new_names_[e];
      }
    return new_name_compute(e);
  }

  template <class E, class Def> void Renamer::visit(E& e, const Def* def)
  {
    // FIXME: Some code was deleted here.
    if (def)
      e.name_set(new_name(def));
  }
} // namespace bind
