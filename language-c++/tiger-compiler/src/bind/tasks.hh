/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

// FIXME: Some code was deleted here.
#pragma once

#include <task/libtask.hh>

namespace bind::tasks
{
  TASK_GROUP("3. Bind");

  DISJUNCTIVE_TASK_DECLARE("bound", " test", "bindings-compute");

  TASK_DECLARE("b|bindings-compute", "compute....", bindings_compute, "parse");

  TASK_DECLARE("B|bindings-display",
               "print the declaration's node address next"
               "to any symbol usage with the pretty printer",

               bindings_display,
               "");

  TASK_DECLARE("rename|rename-ast", "rename ......", rename_ast, "bound");
} // namespace bind::tasks
