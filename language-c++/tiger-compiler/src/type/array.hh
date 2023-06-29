/**
 ** \file type/array.hh
 ** \brief The class Array.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
  /// Array types.
  class Array : public Type
  {
  public:
    Array(const Type& type)
      : array_type_(type)
    {}

    const Type& array_type_;

    const Type& array_type_get() const;

  public:
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;
  };

} // namespace type

#include <type/array.hxx>
