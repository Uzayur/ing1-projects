/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

//namespace bind
#include <bind/binder.hh>
#include <bind/libbind.hh>
#include <bind/renamer.hh>

namespace bind
{
  misc::error bind(ast::Ast& tree)
  {
    Binder bindings_compute;
    bindings_compute(tree);

    return bindings_compute.error_get();
  }

  void rename(ast::Ast& tree)
  {
    auto renamer = Renamer();
    renamer(tree);
  }
} // namespace bind
