/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{
  /// Escapable.
  class Escapable
  {
  public:
    Escapable(bool escapable = true);

    bool escapable_get() const;
    void escapable_set(bool setter);

  protected:
    bool escapable_;
  };
} // namespace ast
#include <ast/escapable.hxx>
