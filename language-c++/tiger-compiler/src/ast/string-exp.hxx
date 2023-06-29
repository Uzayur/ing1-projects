/**
 ** \file ast/string-exp.hxx
 ** \brief Inline methods of ast::StringExp.
 */

#pragma once

#include <ast/string-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const std::string StringExp::string_get() const { return string_; }
  inline std::string StringExp::string_get() { return string_; }
} // namespace ast
