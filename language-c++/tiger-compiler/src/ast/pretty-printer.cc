/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

#include <type/class.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline std::ostream& operator<<(std::ostream& ostr, const Escapable& e)
    {
      // FIXME: Some code was deleted here.
      if (escapes_display(ostr) && e.escapable_get())
        ostr << "/* escaping */ ";

      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (bindings_display(ostr))
        ostr << " /* " << &e << " */";
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    ostr_ << e.var_get() << "." << e.name_get();
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.obj_get() << "[" << e.size_get() << "]"
          << " of " << e.init_get() << misc::incindent;
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << " array of " << e.base_type_get();
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << '(' << e.var_get();
    ostr_ << " := " << e.exp_get() << ')';
  }

  void PrettyPrinter::operator()(const BreakExp& e)
  {
    ostr_ << "break";
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.symbol_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */ ";

    ostr_ << "(";

    if (e.arg_get().empty())
      ostr_ << ")";
    else
      {
        auto count = 0;
        for (auto arg : e.arg_get())
          {
            if (count == 0)
              ostr_ << *arg;
            else
              ostr_ << ", " << *arg;
            count++;
          }
        ostr_ << ")";
      }
  }

  void PrettyPrinter::operator()(const ClassTy& e)
  {
    ostr_ << misc::iendl << "class extends " << e.super_get() << misc::iendl
          << "{";

    for (auto chunk : e.chunks_get())
      ostr_ << misc::incindent << *chunk << misc::decindent;

    ostr_ << misc::iendl << "}" << misc::incindent;
  }

  void PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get() << " = " << e.init_get();
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "(for ";
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */ ";

    ostr_ << e.vardec_get().name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e.vardec_get() << " */ ";

    ostr_ << " := " << *e.vardec_get().init_get() << " to " << e.hi_get()
          << " do" << misc::incendl << '(' << misc::incendl << e.body_get()
          << misc::decendl << ')' << misc::decendl << ')';
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    ostr_ << misc::iendl;

    if (e.body_get() == nullptr)
      ostr_ << "primitive ";
    else
      ostr_ << "function ";

    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */ ";

    ostr_ << "(";

    auto count = 0;
    for (VarDec* vardec : e.formals_get().decs_get())
      {
        if (count != 0)
          ostr_ << ", ";
        ostr_ << vardec->name_get();
        if (bindings_display(ostr_))
          ostr_ << " /* " << vardec << " */ ";
        ostr_ << " : " << *vardec->type_name_get();
        count = 1;
      }
    ostr_ << ")";

    if (e.result_get() != nullptr)
      ostr_ << " : " << *e.result_get();

    if (e.body_get() != nullptr and e.result_get() == nullptr)
      {
        ostr_ << " =" << misc::incendl << "(" << misc::incendl << *e.body_get()
              << misc::decindent;
        if (e.name_get() == "_main")
          ostr_ << misc::iendl;
        ostr_ << ')';
      }

    else if (e.body_get() != nullptr)
      ostr_ << " =" << misc::incendl << *e.body_get();
  }

  void PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "(if " << misc::incindent << e.test_get() << misc::decindent;
    ostr_ << misc::incendl << "then " << misc::incindent << e.thenclause_get()
          << misc::decindent;

    if (&(e.elseclause_get()) != nullptr)
      ostr_ << misc::iendl << "else " << misc::incindent << e.elseclause_get()
            << misc::decindent << ")" << misc::decindent;

    else
      ostr_ << misc::iendl << "else ())" << misc::decindent;
  }

  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }

  void PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::incindent;

    for (auto k : e.chunks_get())
      ostr_ << *k << misc::decindent;

    ostr_ << misc::iendl << "in" << misc::incendl << e.body_get()
          << misc::decendl << "end";
  }

  void PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.obj_get() << "." << e.symbol_get() << "(";

    for (auto a : e.arg_get())
      ostr_ << *a;

    ostr_ << ")";
  }

  void PrettyPrinter::operator()(const MethodDec& e)
  {
    ostr_ << misc::iendl << "method " << e.name_get() << "(";

    auto count = 0;
    for (VarDec* vardec : e.formals_get().decs_get())
      {
        if (count != 0)
          ostr_ << ", ";
        ostr_ << vardec->name_get();
        if (bindings_display(ostr_))
          ostr_ << " /* " << vardec << " */ ";
        ostr_ << " : " << *vardec->type_name_get();
        count = 1;
      }
    ostr_ << ")";

    if (e.result_get() != nullptr)
      ostr_ << " : " << *e.result_get();

    ostr_ << " =" << misc::iendl << '(' << misc::incindent << misc::iendl
          << *e.body_get() << misc::decindent << ')';
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
    auto name = e.name_get();
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      {
        if (e.def_get() != nullptr)
          ostr_ << " /* " << e.def_get() << " */ ";
        else if (name == "string" || name == "int" || name == "Object")
          ostr_ << " /* 0 */ ";
        else
          ostr_ << " /* " << e.def_get() << " */ ";
      }
  }

  void PrettyPrinter::operator()(const NilExp& e) { ostr_ << "nil"; }

  void PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << "new " << e.obj_get() << misc::incindent;
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << '(';
    if (&e.left_get())
      ostr_ << e.left_get() << ' ';

    switch (e.oper_get())
      {
      case OpExp::Oper::add:
        ostr_ << "+";
        break;
      case OpExp::Oper::sub:
        ostr_ << "-";
        break;
      case OpExp::Oper::mul:
        ostr_ << "*";
        break;
      case OpExp::Oper::div:
        ostr_ << "/";
        break;
      case OpExp::Oper::eq:
        ostr_ << "=";
        break;
      case OpExp::Oper::ne:
        ostr_ << "<>";
        break;
      case OpExp::Oper::lt:
        ostr_ << "<";
        break;
      case OpExp::Oper::le:
        ostr_ << "<=";
        break;
      case OpExp::Oper::gt:
        ostr_ << ">";
        break;
      default:
        ostr_ << ">=";
      }
    if (&e.left_get())
      ostr_ << ' ';

    ostr_ << e.right_get() << ')';
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.name_get();
    ostr_ << "{ ";

    auto count = 0;
    for (auto a : e.field_get())
      {
        if (count != 0)
          ostr_ << ", ";
        ostr_ << *a;
        count = 1;
      }

    ostr_ << " }";
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << " {";

    auto count = 0;
    for (auto f : e.fields_get())
      {
        if (count != 0)
          ostr_ << ", ";
        ostr_ << *f;
        count = 1;
      }

    ostr_ << "}" << misc::incindent;
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
    if (e.exp_get().empty())
      ostr_ << "()";
    else
      {
        if (e.exp_get().size() > 2)
          ostr_ << "(";

        auto count = 0;
        for (auto arg : e.exp_get())
          {
            if (count == 0)
              ostr_ << *arg;
            else
              ostr_ << ";" << misc::iendl << *arg;
            count++;
          }
        if (e.exp_get().size() != 2 and e.exp_get().size() != 1)
          ostr_ << ")";
      }
  }

  void PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << "\"" << misc::escape(e.string_get()) << "\"";
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    if (bindings_display(ostr_))
      ostr_ << misc::iendl << "type " << static_cast<const Dec&>(e) << " ="
            << e.ty_get();
    else
      ostr_ << misc::iendl << "type " << e.name_get() << " =" << e.ty_get();
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
    ostr_ << misc::iendl << misc::incindent << "var ";
    const Escapable& escape = e;
    ostr_ << escape;
    if (e.type_name_get() == nullptr)
      {
        if (bindings_display(ostr_))
          ostr_ << static_cast<const Dec&>(e) << misc::decindent;
        else
          ostr_ << e.name_get() << misc::decindent;
      }
    else
      {
        if (bindings_display(ostr_))
          ostr_ << static_cast<const Dec&>(e) << " : " << *e.type_name_get();

        else
          ostr_ << e.name_get() << " : " << *e.type_name_get();
      }

    if (e.init_get() != nullptr)
      ostr_ << " := " << *e.init_get();
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while ";
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */ ";

    ostr_ << e.test_get() << " do ";

    ostr_ << misc::incendl << '(' << misc::incendl << e.body_get()
          << misc::decendl << ')' << misc::decendl;
  }
} // namespace ast
