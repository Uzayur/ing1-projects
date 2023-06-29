/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

// FIXME: Some code was deleted here.

#include <ostream>

#include <ast/libast.hh>
#include <ast/tasks.hh>
#include <bind/libbind.hh>
#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS
#include <common.hh>
#include <misc/xalloc.hh>

namespace bind::tasks
{
  void bindings_compute()
  {
    misc::error err = bind::bind(*ast::tasks::the_program);

    task_error() << err;
    if (err)
      task_error().exit();
  }

  void bindings_display() { ast::bindings_display(std::cout) = true; }

  void rename_ast() { bind::rename(*ast::tasks::the_program); }
} // namespace bind::tasks
