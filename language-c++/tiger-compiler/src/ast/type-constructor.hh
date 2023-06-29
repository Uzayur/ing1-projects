/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */

  class TypeConstructor
  {
    // FIXME: Some code was deleted here.
  public:
    // Setter / Getter
    void create_type_set(const type::Type*);
    const type::Type* created_type_get() const;

    // Acceptor
    virtual void accept(ConstVisitor& v) const = 0;
    virtual void accept(Visitor& v) = 0;

    const type::Type* new_type;
  };
} // namespace ast
#include <ast/type-constructor.hxx>
