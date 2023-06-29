/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>
#include <misc/contract.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  // FIXME: Some code was deleted here (Error reporting).
  void Binder::error(const ast::Ast& loc, const std::string& msg)
  {
    error_ << "error: " << loc.location_get() << ": " << msg << '\n';
  }

  void Binder::check_main(const ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.
    if (e.name_get() == "_main")
      {
        if (fun_scoped_.stack.size() != 1)
          error_ << misc::error::error_type::bind
                 << "error: " << e.location_get()
                 << ": redefinition of function main" << '\n';
      }
  }

  void Binder::break_error(ast::BreakExp& e)
  {
    error_ << misc::error::error_type::bind << "error: " << e.location_get()
           << ": 'break' outside any loop" << '\n';
  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/

  void Binder::scope_begin()
  {
    // FIXME: Some code was deleted here.
    fun_scoped_.scope_begin();
    var_scoped_.scope_begin();
    ty_scoped_.scope_begin();
  }

  void Binder::scope_end()
  {
    // FIXME: Some code was deleted here.
    fun_scoped_.scope_end();
    var_scoped_.scope_end();
    ty_scoped_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.
  void Binder::operator()(ast::Ast& ast)
  {
    scope_begin();
    ast.accept(*this);
    scope_end();
  }

  void Binder::operator()(ast::LetExp& e)
  {
    scope_begin();

    e.chunks_get().accept(*this);
    e.body_get().accept(*this);

    scope_end();
  }

  void Binder::operator()(ast::ForExp& e)
  {
    scope_begin();

    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);

    loop_vec.push_back(&e);
    e.body_get().accept(*this);
    loop_vec.pop_back();

    scope_end();
  }

  void Binder::operator()(ast::WhileExp& e)
  {
    scope_begin();

    e.test_get().accept(*this);

    loop_vec.push_back(&e);
    e.body_get().accept(*this);
    loop_vec.pop_back();

    scope_end();
  }

  void Binder::operator()(ast::VarDec& e)
  {
    if (e.type_name_get())
      e.type_name_get()->accept(*this);

    if (e.init_get())
      e.init_get()->accept(*this);

    var_scoped_.put(e.name_get(), &e);
  }

  /*---------.
  | Usages.  |
  `---------*/

  void Binder::operator()(ast::BreakExp& e)
  {
    if (loop_vec.size() == 0)
      break_error(e);
    else
      e.def_set(loop_vec.back());
  }

  void Binder::operator()(ast::CallExp& e)
  {
    auto name = e.symbol_get();

    for (auto k = fun_scoped_.stack.size() - 1; k > 0; --k)
      {
        auto iterator = fun_scoped_.stack[k].find(name);
        if (iterator != fun_scoped_.stack[k].end())
          {
            e.def_set(iterator->second);

            super_type::operator()(e);
            return;
          }
      }
    undeclared("function", e);
  }

  void Binder::operator()(ast::SimpleVar& e)
  {
    auto name = e.name_get();

    for (auto k = var_scoped_.stack.size() - 1; k > 0; --k)
      {
        auto iterator = var_scoped_.stack[k].find(name);
        if (iterator != var_scoped_.stack[k].end())
          {
            e.def_set(iterator->second);
            return;
          }
      }
    undeclared("variable", e);
  }

  void Binder::operator()(ast::NameTy& e)
  {
    auto name = e.name_get();

    for (auto k = ty_scoped_.stack.size() - 1; k > 0; --k)
      {
        auto iterator = ty_scoped_.stack[k].find(name);
        if (iterator != ty_scoped_.stack[k].end())
          {
            e.def_set(iterator->second);
            return;
          }
      }
    if (name != "int" && name != "string" && name != "Object")
      undeclared("type", e);
  }

  /*-------------------.
  | Visiting VarChunk. |
  `-------------------*/

  // FIXME: Some code was deleted here.
  void Binder::operator()(ast::VarChunk& e) { chunk_visit(e); }

  template <> inline void Binder::visit_dec_header<ast::VarDec>(ast::VarDec& e)
  {
    var_scoped_.put(e.name_get(), &e);
  }

  template <> inline void Binder::visit_dec_body<ast::VarDec>(ast::VarDec& e)
  {
    e.accept(*this);
  }

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/
  void Binder::operator()(ast::FunctionChunk& e) { chunk_visit(e); }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/
  // FIXME: Some code was deleted here.

  void Binder::operator()(ast::TypeChunk& e) { chunk_visit(e); }

  template <>
  inline void Binder::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    ty_scoped_.put(e.name_get(), &e);
  }

  template <> inline void Binder::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    e.accept(*this);
  }

} // namespace bind
