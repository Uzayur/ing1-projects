/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <string>
#include <ast/exp.hh>

namespace ast
{
  /// StringExp.
  class StringExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    StringExp(const Location& location, const std::string& string);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const std::string string_get() const;
    std::string string_get();

  protected:
    std::string string_;
  };
} // namespace ast
#include <ast/string-exp.hxx>
