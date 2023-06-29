/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <memory>

#include <ast/all.hh>
#include <range/v3/view/iota.hpp>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{
  namespace
  {
    // Try to cast the type into a nil type.
    // If it's not actually a `type::Nil`, return `nullptr`.
    // This allows us to write more clear code like:
    // if (auto nil = to_nil(e.type_get())
    // ...
    const Nil* to_nil(const Type& type)
    {
      return dynamic_cast<const Nil*>(&type.actual());
    }

  } // namespace

  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type* TypeChecker::type(ast::Typable& e)
  {
    // FIXME: Some code was deleted here.
    if (e.type_get() == nullptr)
      e.accept(*this);
    return e.type_get();
  }

  const Record* TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    // FIXME: Some code was deleted here.
    for (auto formals : e)
      res->field_add(
        Field(formals->name_get(), *type(formals->type_name_get())));

    return res;
  }

  const Record* TypeChecker::type(const ast::VarChunk& e)
  {
    auto res = new Record;
    for (const auto& var : e)
      res->field_add(var->name_get(), *type(*var));

    return res;
  }

  const misc::error& TypeChecker::error_get() const { return error_; }

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type << ast.location_get() << ": " << msg
           << std::endl;
  }

  void TypeChecker::type_mismatch(const ast::Ast& ast,
                                  const std::string& exp1,
                                  const Type& type1,
                                  const std::string& exp2,
                                  const Type& type2)
  {
    error_ << misc::error::error_type::type << ast.location_get()
           << ": type mismatch" << misc::incendl << exp1 << " type: " << type1
           << misc::iendl << exp2 << " type: " << type2 << misc::decendl;
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const Type& type1,
                                const std::string& exp2,
                                const Type& type2)
  {
    // FIXME: Some code was deleted here.
    if (!type1.compatible_with(type2))
      this->type_mismatch(ast, exp1, type1, exp2, type2);
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    // FIXME: Some code was deleted here (Check types).
    this->check_types(ast, exp1, *type1.type_get(), exp2, *type2.type_get());
  }

  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::SimpleVar& e)
  {
    // FIXME: Some code was deleted here.
    type_default(e, type(*e.def_get()));
  }

  void TypeChecker::operator()(ast::SubscriptVar& e)
  {
    // FIXME: Some code was deleted here.
        auto my_cast = dynamic_cast<const type::Array*>(&type(e.var_get())->actual());
    if (my_cast == nullptr)
        error(e, "SusbscriptVar: not an array");
    else
    {
        e.index_get().accept(*this);
        this->check_types(e, "SusbscriptVar", *type(e.index_get()), "need an Int for index",
                          Int::instance());
        type_default(e, &my_cast->array_type_get());
    }
  }

  void TypeChecker::operator()(ast::FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    auto my_cast = dynamic_cast<const type::Record*>(&type(e.var_get())->actual());
    if (my_cast == nullptr)
        error(e, "this var is not a record");

    else
    {
        for (auto arg : my_cast->fields_get())
        {
            if (arg.name_get() == e.name_get())
            {
                auto cast = dynamic_cast<const type::Record*>(&type(e.var_get())->actual());
                if (cast)
                {
                    type_default(e, cast->field_type(e.name_get()));
                    return;
                }
                else
                {
                    error(e, "FieldVar not with a record");
                    return;
                }
            }
        }
        error(e, "member not in record");
    }
  }

  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void TypeChecker::operator()(ast::IntExp& e)
  {
    // FIXME: Some code was deleted here.
    type_default(e, &Int::instance());
  }

  void TypeChecker::operator()(ast::StringExp& e)
  {
    // FIXME: Some code was deleted here.
    type_default(e, &String::instance());
  }

  // Complex values.

  void TypeChecker::operator()(ast::RecordExp& e)
  {
    // If no error occured, check for nil types in the record initialization.
    // If any error occured, there's no need to set any nil types.
    // If there are any record initializations, set the `record_type_`
    // of the `Nil` to the expected type.
    // FIXME: Some code was deleted here.
    auto const type_name = type(e.name_get());
    const auto& rec = dynamic_cast<const type::Record*>(&type_name->actual());
    if (rec)
      {
        auto& field = e.field_get();
        if (rec->fields_get().size() == field.size())
          {
            for (auto i = 0; i < field.size(); i++)
              check_types(e, "RecordExp", rec->fields_get()[i].type_get(), "not same type",
                          *type(field[i]->init_get()));
            e.type_set(rec);
          }
        else
            error(e, "is not a record type");
      }
    else
        error(e, "is not a record type");
  }

  void TypeChecker::operator()(ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.

    // If any of the operands are of type Nil, set the `record_type_` to the
    // type of the opposite operand.
    if (e.oper_get() == ast::OpExp::Oper::add
        || e.oper_get() == ast::OpExp::Oper::sub
        || e.oper_get() == ast::OpExp::Oper::mul
        || e.oper_get() == ast::OpExp::Oper::div)
      {
        this->check_types(e, "op_lhs", *type(e.left_get()), "need an Int",
                          Int::instance());
        this->check_types(e, "op_rhs", *type(e.right_get()), "need an Int",
                          Int::instance());
        type_default(e, &Int::instance());
      }

    else if (e.oper_get() == ast::OpExp::Oper::eq
             || e.oper_get() == ast::OpExp::Oper::ne
             || e.oper_get() == ast::OpExp::Oper::lt
             || e.oper_get() == ast::OpExp::Oper::le
             || e.oper_get() == ast::OpExp::Oper::gt
             || e.oper_get() == ast::OpExp::Oper::ge)
    {
      this->check_types(e, "operation", e.left_get(),
                        "need same type with this operand",
                        e.right_get());
      type_default(e, &Int::instance());
    }

    if (!error_)
      {
        // FIXME: Some code was deleted here.
        // a faire pour les op de comparaison (si un est nil l'autre est un record)
        auto nul1 = to_nil(*type(e.left_get()));
        auto nul2 = to_nil(*type(e.right_get()));

        if (nul1)
          nul1->record_type_set(*type(e.left_get()));
        else if (nul2)
          nul2->record_type_set(*type(e.right_get()));
      }
  }

  // FIXME: Some code was deleted here.
  void TypeChecker::operator()(ast::SeqExp& e)
  {
    if (e.exp_get().size() == 0)
      type_default(e, &Void::instance());
    else
      {
        for (auto exp : e.exp_get())
          exp->accept(*this);

        type_default(e, type(*e.exp_get().back()));
      }
  }

  void TypeChecker::operator()(ast::WhileExp& e)
  {
    e.test_get().accept(*this);

    check_types(e, "while", Void::instance(), "result type not void",
                *type(e.body_get()));
    type_default(e, &Void::instance());
  }

  void TypeChecker::operator()(ast::ForExp& e)
  {
    type_default(e, &Void::instance());
    e.vardec_get().accept(*this);
    if (error_)
        return;

    check_types(e, "for vardec", Int::instance(), "type not int",
                *type(e.vardec_get()));
    if (error_)
        return;

    var_read_only_.insert(&e.vardec_get());

    e.hi_get().accept(*this);
    if (error_)
        return;

    check_types(e, "for limit", Int::instance(), "type not int",
                *type(e.hi_get()));
    if (error_)
        return;

    auto hi_cast = dynamic_cast<ast::IntExp*>(&e.hi_get());
    auto init_cast = dynamic_cast<ast::IntExp*>(e.vardec_get().init_get());
    if (hi_cast && init_cast && hi_cast->value_get() < init_cast->value_get())
    {
        error(e, "hi less than assign");
        return;
    }

    e.body_get().accept(*this);
    if (error_)
        return;

    var_read_only_.erase(&e.vardec_get());

    check_types(e, "for", Void::instance(), "result type not void",
                *type(e.body_get()));
    if (error_)
        return;

  }

  void TypeChecker::operator()(ast::AssignExp& e)
  {
    e.var_get().accept(*this);

    if (error_)
        return;

    auto var = dynamic_cast<const ast::SimpleVar*>(&e.var_get());
    if (var != nullptr)
    {
        if (var_read_only_.contains(var->def_get()))
        {
          error(e, "Try to modifie a read only var");
          return;
        }

        auto cast_nil = to_nil(*type(e.exp_get()));
        if (cast_nil)
        {
            auto cast_record = dynamic_cast<const type::Record*>(&type(e.var_get())->actual());
            if (cast_record != nullptr)
            {
                type_default(e, &Void::instance());
                return;
            }
        }

        check_types(e, "exp", *type(e.exp_get()), "var",
                    *type(e.var_get()));
        type_default(e, &Void::instance());
    }

    else
    {
      check_types(e, "assign", *type(e.exp_get()), "not same type",
                    *type(e.var_get()));
      type_default(e, &Void::instance());
    }
  }

  void TypeChecker::operator()(ast::LetExp& e)
  {
    e.chunks_get().accept(*this);
    e.body_get().accept(*this);

    type_default(e, type(e.body_get()));
  }

  void TypeChecker::operator()(ast::IfExp& e)
  {
    e.test_get().accept(*this);
    e.thenclause_get().accept(*this);

    if (&e.elseclause_get() != nullptr)
    {
        e.elseclause_get().accept(*this);
        check_types(e, "if", *type(e.thenclause_get()), "not same type with if and else",
                       *type(e.elseclause_get()));
    }

    else
    {
        check_types(e, "if", *type(e.thenclause_get()), "not same type with if and else",
                    Void::instance());
    }

    type_default(e, type(e.thenclause_get()));
  }

  void TypeChecker::operator()(ast::BreakExp& e)
  {
    type_default(e, &Void::instance());
  }

  void TypeChecker::operator()(ast::CallExp& e)
  {
    if (e.def_get() != nullptr)
      {
        auto rec = type(e.def_get()->formals_get());
        auto index = 0;

        if (rec->fields_get().size() != e.arg_get().size())
          {
            error(e, "Wrong number of args in call-exp");
            return;
          }

        for (auto args : rec->fields_get())
          {
            this->check_types(e, "args call-exp", args.type_get(), "wrong type",
                              *type(*e.arg_get()[index]));
            index++;
          }

        if (e.def_get()->result_get() != nullptr)
          type_default(e, type(*e.def_get()->result_get()));
        else
          type_default(e, &Void::instance());
      }
  }

  void TypeChecker::operator()(ast::ArrayExp& e)
  {
    e.obj_get().accept(*this);
    e.size_get().accept(*this);
    e.init_get().accept(*this);

    check_types(e, "size", *type(e.size_get()), "not a int", Int::instance());


    auto array = dynamic_cast<const type::Array*>(&type(e.obj_get())->actual());
    if (array)
    {
        check_types(e, "ArrayExp", *type(e.init_get()), "bad type in array",
                    array->array_type_get());
    }
    else
    {
        error(e, "not an array", type(e.obj_get()));
    }

    type_default(e, array);
  }

  void TypeChecker::operator()(ast::CastExp& e)
  {
    e.exp_get().accept(*this);
    e.ty_get().accept(*this);
    e.type_set(type(e.ty_get()));
  }

  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  void TypeChecker::operator()(ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionDec>(e);
  }

  void TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store the type of this fun.
  template <>
  void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.
    auto rec = type(e.formals_get());

    if (e.result_get() == nullptr)
      {
        auto func = new Function(rec, Void::instance());
        type_default(e, func);
        created_type_default(e, func);
      }
    else
      {
        auto func = new Function(rec, *type(*e.result_get()));
        type_default(e, func);
        created_type_default(e, func);
      }
  }

  // Type check this function's body.
  template <>
  void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      {
        visit_routine_body<Function>(e);

        // Check for Nil types in the function body.
        if (!error_)
          {
            // FIXME: Some code was deleted here.
            // le body dooit renvoyer un typt nil
            // seulement si la fonction renvoie un
            // type record.
            auto nil = to_nil(*type(*e.body_get()));
            if (nil)
              nil->record_type_set(*type(*e.result_get()));
          }
      }
  }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
    // FIXME: Some code was deleted here.
    if (e.init_get() == nullptr)
      e.type_set(type(*e.type_name_get()));

    else if (e.type_name_get() == nullptr)
    {
      auto nil = to_nil(*type(*e.init_get()));
      if (nil)
      {
        error(e, "initializing a vardec with nil type");
        return;
      }
      e.type_set(type(*e.init_get()));
    }

    else
      {
        check_types(e, "vardec", *type(*e.type_name_get()),
                    "unvalid declared type", *type(*e.init_get()));
        type_default(e, type(*e.type_name_get()));
      }
  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/

  void TypeChecker::operator()(ast::TypeChunk& e)
  {
    chunk_visit<ast::TypeDec>(e);
  }

  void TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store this type.
  template <> void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
    // FIXME: Some code was deleted here.
    type::Type* named = new Named(e.name_get());
    e.type_set(named);
    e.create_type_set(named);
  }

  // Bind the type body to its name.
  template <> void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // FIXME: Some code was deleted here.
    auto named = dynamic_cast<const Named*>(e.type_get());
    named->type_set(type(e.ty_get()));

    if (!named->sound())
      {
        error(e, "type recursive");
        named->type_set(&Void::instance());
      }
  }

  /*------------------.
  | Visiting /Chunk/. |
  `------------------*/

  template <class D> void TypeChecker::chunk_visit(ast::Chunk<D>& e)
  {
    // FIXME: Some code was deleted here.
    for (auto elem : e.decs_get())
      {
        visit_dec_header(*elem);
      }

    for (auto elem : e.decs_get())
      {
        visit_dec_body(*elem);
      }
  }

  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void TypeChecker::operator()(ast::NameTy& e)
  {
    // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).
    if (e.name_get() == "int")
        type_default(e, &Int::instance());

    else if (e.name_get() == "string")
        type_default(e, &String::instance());

    else
        type_default(e, e.def_get()->type_get());
  }

  void TypeChecker::operator()(ast::RecordTy& e)
  {
    // FIXME: Some code was deleted here.
    auto record = type(e.fields_get());
    auto set = std::set<misc::symbol>();
    for (auto var : e.fields_get())
      {
        if (set.contains(var->name_get()))
          {
            error(e, "set field_name already contains name");
          }
        else
          {
            set.insert(var->name_get());
          }
      }
    type_default(e, record);
    e.type_set(record);
    e.create_type_set(record);

    // il faut aussiva verifier que qu'il n' y ait pas 2 trucs
    // de meme nom dans les fields
    // pour cela tu cree un set ou tu vas mettre tous les name,
    // a chaque fois que tu y rajoutes quelque chose, tu tcheck
    // juste s'il y est deja. si cest le ca tu retournes une erreur.
  }

  void TypeChecker::operator()(ast::ArrayTy& e)
  {
    // FIXME: Some code was deleted here.
    auto new_arr = new Array(*type(e.base_type_get()));
    type_default(e, new_arr);
    e.type_set(new_arr);
    e.create_type_set(new_arr);

    // on cree un type array qui a un visiteur type
    // dans le hh et ce visiteur la c'est un namety>
    // on appliaique juste type sur lui comme dans la fonction precedente
  }
} // namespace type
