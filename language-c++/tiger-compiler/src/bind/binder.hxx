/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  // FIXME: Some code was deleted here (Error reporting).
  template <typename T>
  void Binder::undeclared(const std::string& k, const T& e)
  {
    error_ << misc::error::error_type::bind << "error: " << e.location_get()
           << ": undeclared " << k << ": " << e.name_get() << '\n';
  }

  template <typename T> void Binder::redefinition(const T& e1, const T& e2)
  {
    error_ << misc::error::error_type::bind << "error: " << e2.location_get()
           << ": redefinition: " << e1.name_get() << '\n'
           << e1.location_get() << ": first definition" << '\n';
  }

  /*----------------------------.
  | Visiting /ChunkInterface/.  |
  `----------------------------*/

  template <class D> void Binder::chunk_visit(ast::Chunk<D>& e)
  {
    // Shorthand.
    using chunk_type = ast::Chunk<D>;

    auto chunks_memory = std::vector<D*>();
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    for (auto elem : e.decs_get())
      {
        for (auto elt : chunks_memory)
          {
            if (elt->name_get() == elem->name_get())
              redefinition(*elt, *elem);
          }

        chunks_memory.push_back(elem);
        visit_dec_header(*elem);
      }

    for (auto elem : e.decs_get())
      visit_dec_body(*elem);
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // FIXME: Some code was deleted here.

  template <> inline void Binder::visit_dec_header(ast::FunctionDec& e)
  {
    check_main(e);
    fun_scoped_.put(e.name_get(), &e);
  }

  template <> inline void Binder::visit_dec_body(ast::FunctionDec& e)
  {
    scope_begin();
    e.accept(*this);
    scope_end();
  }

} // namespace bind
