                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.value.type variant
%define api.token.constructor

// We use a GLR parser because it is able to handle Shift-Reduce and
// Reduce-Reduce conflicts by forking and testing each way at runtime. GLR
// permits, by allowing few conflicts, more readable and maintainable grammars.
%glr-parser
%skeleton "glr2.cc"

// In TC, we expect the GLR to resolve one Shift-Reduce and zero Reduce-Reduce
// conflict at runtime. Use %expect and %expect-rr to tell Bison about it.
  // FIXME: Some code was deleted here (Other directives).

%expect 1
%expect-rr 0

%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define api.filename.type {const std::string}
%locations

// The parsing context.
%param { ::parse::TigerParser& tp }

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

%code provides
{
  // Announce to Flex the prototype we want for lexing (member) function.
  # define YY_DECL_(Prefix)                               \
    ::parse::parser::symbol_type                          \
    (Prefix parselex)(::parse::TigerParser& tp)
  # define YY_DECL YY_DECL_(yyFlexLexer::)
}

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/chunk.hh>
# include <ast/chunk-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).


/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/scantiger.hh>
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>
# include <parse/tiger-driver.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }

  /// Use our local scanner object.
  inline
  ::parse::parser::symbol_type
  parselex(parse::TigerParser& tp)
  {
    return tp.scanner_->parselex(tp);
  }
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       EXP          "_exp"
       CAST         "_cast"
       LVALUE       "_lvalue"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"
       CHUNKS       "_chunks"
       NAMETY       "_namety"

%type <ast::Exp*>             exp
%type <ast::ChunkList*>       chunks

%type <ast::TypeChunk*>       tychunk
%type <ast::TypeDec*>         tydec
%type <ast::NameTy*>          typeid
%type <ast::Ty*>              ty

%type <ast::Field*>           tyfield
%type <ast::fields_type*>     tyfields tyfields.1
  // FIXME: Some code was deleted here (More %types).

%type <ast::exps_type*>           exps
%type <ast::exps_type*>           exps_req

%type <ast::Var*>                 lvalue

%type <ast::FunctionChunk*>       funchunk
%type <ast::VarChunk*>            varchunk

%type <ast::FunctionDec*>         fundec
%type <ast::fieldinits_type*>     expopt2
%type <ast::fieldinits_type*>     expopt21
%type <ast::exps_type*>           expopt3
%type <ast::exps_type*>           expopt31
%type <ast::ChunkList*>           classfields
%type <ast::ChunkInterface*>      classfield
%type <ast::MethodChunk*>         methodchunk
%type <ast::VarChunk*>            tyfieldschunk.1
%type <ast::VarChunk*>            tyfieldschunk
%type <ast::VarDec*>              tyfieldchunk
%type <ast::MethodDec*>           methoddec


  // FIXME: Some code was deleted here (Priorities/associativities).
%precedence THEN DO OF ASSIGN
%precedence ELSE


%left OR
%left AND

%nonassoc GE LE EQ NE LT GT
%left PLUS MINUS
%left TIMES DIVIDE

%precedence CHUNKS
%precedence TYPE
%precedence PRIMITIVE FUNCTION METHOD CLASS


// Solving conflicts on:
// let type foo = bar
//     type baz = bat
// which can be understood as a list of two TypeChunk containing
// a unique TypeDec each, or a single TypeChunk containing two TypeDec.
// We want the latter.

%start program

%%
program:
  /* Parsing a source program.  */
  exp             { tp.ast_ = $1; }
| /* Parsing an imported file.  */
  chunks          { tp.ast_ = $1; }
;

exps:
  %empty          { $$ = tp.td_.make_exps_type(); }
| exp exps_req    { $$ = $2; $$->insert($$->begin(), $1); }
;

exps_req:
  %empty              { $$ = tp.td_.make_exps_type(); }
| ";" exp exps_req    { $$ = $3; $$->insert($$->begin(), $2); }
;

exp:
  "nil"             { $$ = tp.td_.make_NilExp(@$); }
| INT               { $$ = tp.td_.make_IntExp(@$, $1); }
| STRING            { $$ = tp.td_.make_StringExp(@$, $1); }

| "_namety" "(" INT ")" "[" exp "]" "of" exp  { $$ = tp.td_.make_ArrayExp(@$, metavar<ast::NameTy>(tp, $3), $6, $9 ); }
| ID "[" exp "]" "of" exp                     { $$ = tp.td_.make_ArrayExp(@$, tp.td_.make_NameTy(@$, $1), $3, $6); }

| typeid "{" expopt2 "}"            { $$ = tp.td_.make_RecordExp(@$, $1, $3); }

| lvalue                            { $$ = $1; }

| ID "(" expopt3 ")"                { $$ = tp.td_.make_CallExp(@$, $1, $3); }

| "-" exp         { $$ = tp.enable_extensions().parse(Tweast() << "0 - " << $2); }
| exp "+" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
| exp "-" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
| exp "*" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
| exp "/" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
| exp "=" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
| exp "<>" exp    { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
| exp ">" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
| exp "<" exp     { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
| exp ">=" exp    { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
| exp "<=" exp    { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
| exp "&" exp     { $$ = tp.enable_extensions().parse(Tweast() << "if " << $1 << " then " << $3 << " <> 0 else 0"); }
| exp "|" exp     { $$ = tp.enable_extensions().parse(Tweast() << "if " << $1 << " then 1 else " << $3); }
| "(" exps ")"    { $$ = tp.td_.make_SeqExp(@$, $2); }

| lvalue ":=" exp                       { $$ = tp.td_.make_AssignExp(@$, $1, $3); }

| "if" exp "then" exp                   { $$ = tp.td_.make_IfExp(@$, $2, $4); }
| "if" exp "then" exp "else" exp        { $$ = tp.td_.make_IfExp(@$, $2, $4, $6); }
| "while" exp "do" exp                  { $$ = tp.td_.make_WhileExp(@$, $2, $4); }
| "for" ID ":=" exp "to" exp "do" exp   { $$ = tp.td_.make_ForExp(@$,tp.td_.make_VarDec(@$, $2, nullptr, $4), $6, $8); }
| "break"                               { $$ = tp.td_.make_BreakExp(@$); }
| "let" chunks "in" exps "end"          { $$ = tp.td_.make_LetExp(@$, $2,tp.td_.make_SeqExp(@$, $4)); }

| "new" typeid                          { $$ = tp.td_.make_ObjectExp(@$, $2); }
| lvalue "." ID "(" expopt3 ")"         { $$ = tp.td_.make_MethodCallExp(@$, $3, $5, $1); }

| "_cast" "(" exp "," ty ")"            { $$ = tp.td_.make_CastExp(@$, $3, $5); }
| "_exp" "(" INT ")"                    { $$ = metavar<ast::Exp>(tp, $3); }
;

expopt2:
  %empty                    { $$ = tp.td_.make_fieldinits_type(); }
| ID "=" exp expopt21       { $$ = $4; $$->insert($$->begin(), tp.td_.make_FieldInit(@$, $1, $3)); }
;

expopt21:
  %empty                    { $$ = tp.td_.make_fieldinits_type(); }
| "," ID "=" exp expopt21   { $$ = $5; $$->insert($$->begin(), tp.td_.make_FieldInit(@$, $2, $4)); }
;

expopt3:
  %empty                    { $$ = tp.td_.make_exps_type(); }
| exp expopt31              { $$ = $2; $$->insert($$->begin(), $1); }
;

expopt31:
  %empty                    { $$ = tp.td_.make_exps_type(); }
| "," exp expopt31          { $$ = $3; $$->insert($$->begin(), $2);}
;

lvalue:
  ID                        { $$ = tp.td_.make_SimpleVar(@$, $1); }
| lvalue "." ID             { $$ = tp.td_.make_FieldVar(@$, $1, $3); }
| lvalue "[" exp "]"        { $$ = tp.td_.make_SubscriptVar(@$, $1, $3); }

| "_lvalue" "(" INT ")"     { $$ = metavar<ast::Var>(tp, $3); }
;

/*---------------.
| Declarations.  |
`---------------*/

  /* Chunks are contiguous series of declarations of the same type
     (TypeDec, FunctionDec...) to which we allow certain specfic behavior like
     self referencing.
     They are held by a ChunkList, that can be empty, like in this case:
        let
        in
            ..
        end
     which is why we end the recursion with a %empty. */

chunks:
  %empty                  { $$ = tp.td_.make_ChunkList(@$); }
| tychunk chunks          { $$ = $2; $$->push_front($1); }
| funchunk chunks         { $$ = $2; $$->push_front($1); }
| varchunk chunks         { $$ = $2; $$->push_front($1); }
| "_chunks" "(" INT ")" chunks { $$ = $5; $$->splice_front(*metavar<ast::ChunkList>(tp, $3)); }

// Importing a set of declarations
| "import" STRING chunks  { $$ = $3; auto res = tp.parse_import($2, @$); if (res != nullptr) {$$->splice_front(*res);}; }
;

/*--------------------.
| Type Declarations.  |
`--------------------*/

varchunk:
  "var" ID ":=" exp            { $$ = tp.td_.make_VarChunk(@$); $$->push_front(*tp.td_.make_VarDec(@$, $2, nullptr, $4)); }
| "var" ID ":" typeid ":=" exp { $$ = tp.td_.make_VarChunk(@$); $$->push_front(*tp.td_.make_VarDec(@$, $2, $4, $6)); }
;

funchunk:
  fundec %prec CHUNKS   { $$ = tp.td_.make_FunctionChunk(@1); $$->push_front(*$1); }
| fundec funchunk       { $$ = $2; $$->push_front(*$1); }
;

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS  { $$ = tp.td_.make_TypeChunk(@1); $$->push_front(*$1);}
| tydec tychunk       { $$ = $2; $$->push_front(*$1); }
;

fundec:
  "function" ID "(" tyfieldschunk ")" "=" exp            { $$ = tp.td_.make_FunctionDec(@$, $2, $4, nullptr, $7); }
| "function" ID "(" tyfieldschunk ")" ":" typeid "=" exp { $$ = tp.td_.make_FunctionDec(@$, $2, $4, $7, $9); }

| "primitive" ID "(" tyfieldschunk ")"                   { $$ = tp.td_.make_FunctionDec(@$, $2, $4, nullptr, nullptr); }
| "primitive" ID "(" tyfieldschunk ")" ":" typeid        { $$ = tp.td_.make_FunctionDec(@$, $2, $4, $7, nullptr); }
;

tydec:
  "type" ID "=" ty                                  { $$ = tp.td_.make_TypeDec(@$, $2, $4); }
| "class" ID "{" classfields "}"                    { $$ = tp.td_.make_TypeDec(@$, $2, tp.td_.make_ClassTy(@$, tp.td_.make_NameTy(@$, misc::symbol("Object")), $4)); }
| "class" ID "extends" typeid "{" classfields "}"   { $$ = tp.td_.make_TypeDec(@$, $2, tp.td_.make_ClassTy(@$, $4, $6)); }
;

ty:
  typeid                      { $$ = $1; }
| "{" tyfields "}"       { $$ = tp.td_.make_RecordTy(@$, $2); }
| "array" "of" typeid         { $$ = tp.td_.make_ArrayTy(@$, $3); }

| "class" "{" classfields "}"                   { $$ = tp.td_.make_ClassTy(@$, tp.td_.make_NameTy(@$, misc::symbol("Object")), $3); }
| "class" "extends" typeid "{" classfields "}"  { $$ = tp.td_.make_ClassTy(@$, $3, $5); }
;

tyfieldschunk:
  %empty            { $$ = tp.td_.make_VarChunk(@$); }
| tyfieldschunk.1   { $$ = $1; }
;

tyfieldschunk.1:
  tyfieldschunk.1 "," tyfieldchunk  { $$ = $1; $$->emplace_back(*$3); }
| tyfieldchunk                      { $$ = tp.td_.make_VarChunk(@$); $$->emplace_back(*$1); }
;

tyfieldchunk:
  ID ":" typeid    { $$ = tp.td_.make_VarDec(@$, $1, $3, nullptr); }
;

tyfields:
  %empty               { $$ = tp.td_.make_fields_type(); }
| tyfields.1           { $$ = $1; }
;


tyfields.1:
  tyfields.1 "," tyfield { $$ = $1; $$->emplace_back($3); }
| tyfield                { $$ = tp.td_.make_fields_type($1); }
;

tyfield:
  ID ":" typeid     { $$ = tp.td_.make_Field(@$, $1, $3); }
;

typeid:
  ID                    { $$ = tp.td_.make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| "_namety" "(" INT ")" { $$ = metavar<ast::NameTy>(tp, $3); }
;

classfields:
  %empty                             { $$ = tp.td_.make_ChunkList(@$); }
| classfield classfields             { $$ = $2; $$->push_front($1); }
;

classfield:
  varchunk                  { $$ = $1; }
| methodchunk               { $$ = $1; }
;

methodchunk:
  methoddec %prec CHUNKS    { $$ = tp.td_.make_MethodChunk(@1); $$->push_front(*$1); }
| methoddec methodchunk     { $$ = $2; $$->push_front(*$1); }
;

methoddec:
  "method" ID "(" tyfieldschunk ")" "=" exp              {$$ = tp.td_.make_MethodDec(@$, $2, $4, nullptr, $7); }
| "method" ID "(" tyfieldschunk ")" ":" typeid "=" exp   {$$ = tp.td_.make_MethodDec(@$, $2, $4, $7, $9); }
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  // FIXME: Some code was deleted here.
  tp.error_ << misc::error::error_type::parse
            << l
            << m
            << std::endl;
}
