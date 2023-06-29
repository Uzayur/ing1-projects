                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

  // FIXME: Some code was deleted here.

// Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier (l.41): `"     \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

# define CHECK_OBJECT()                                 \
  do {                                                  \
    if (!tp.enable_object_extensions_p_)                \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier (l.50): `"     \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
symbol          ([a-zA-Z]([a-zA-Z]|\_|[0-9])*|\_main)
  /* FIXME: Some code was deleted here. */

%%
%{
  // FIXME: Some code was deleted here (Local variables).
  std::string grown_string;
  // Each time yylex is called.
  tp.location_.step();
  int return_count = 0;
%}

 /* The rules.  */

{int}         {
                int val = 0;
                try
                {
                    val = std::stoi(yytext);
                }catch(std::exception& e)
                {
                    tp.error_ << misc::error::error_type::scan
                    << tp.location_
                    << ": invalid int (l.70): `"
                    << misc::escape(yytext) << "'\n";
                }

                return TOKEN_VAL(INT, val);
              }
\\n {
  tp.error_ << misc::error::error_type::scan
           << tp.location_
           << "backslash n out of a string (l.87): '"
           << misc::escape(yytext) << "'\n";
}

\\[0-7]{3} {
  tp.error_ << misc::error::error_type::scan
           << tp.location_
           << "backslash oct out of a string (l.94): '"
           << misc::escape(yytext) << "'\n";
}

"/*"     return_count++; BEGIN SC_COMMENT;

<SC_COMMENT>{

    "*/" {
        return_count--;
        if (return_count == 0)
            BEGIN INITIAL;
    }
    \n {
        grown_string.append(1, '\n');
        tp.location_.lines();
    }

    "/*" {return_count++;}

    <<EOF>> {
        tp.error_ << misc::error::error_type::scan
                  << tp.location_
                  << ": unterminated comment (l.117): '"
                  << misc::escape(yytext) << "'"<< std::endl;
        BEGIN INITIAL;
    }

    . {continue;}

}

"\""        grown_string.clear(); BEGIN SC_STRING;

<SC_STRING>{ /* Handling of the strings.  Initial " is eaten. */
  "\"" {
    BEGIN INITIAL;
    return TOKEN_VAL(STRING, grown_string);
  }

  \\x[0-9a-fA-F]{2}  {
    grown_string.append(1, strtol(yytext + 2, 0, 16));
  }

  \\[0-7]{3} {
      if (yytext[1] > '3' or yytext[2] > '7' or yytext[3] > '7')
      {
          tp.error_ << misc::error::error_type::scan
                    << tp.location_
                    << ": erreur num (l.149): `"
                    << misc::escape(yytext) << "\n";

      }

      grown_string.append(1, strtol(yytext + 1, 0, 8));

  }

  \\a {
      grown_string.append(1, '\a');
  }

  \\b {
      grown_string.append(1, '\b');
  }

  \\f {
      grown_string.append(1, '\f');
  }

  \\n {
      grown_string.append(1, '\n');
      tp.location_.lines();

  }

  \n {tp.location_.lines();}

  \\r {
      grown_string.append(1, '\r');
  }

  \\t {
      grown_string.append(1, '\t');
  }

  \\v {
      grown_string.append(1, '\v');
  }

  \\\" {
      grown_string.append(1, '\"');
  }

  \\\\ {
      grown_string.append(1, '\\');
  }

  \\. {
      tp.error_ << misc::error::error_type::scan
                    << tp.location_
                    << ": backslash error in string (l.200):'"
                    << misc::escape(yytext) << "'\n";
  }

  <<EOF>> {
      tp.error_ << misc::error::error_type::scan
                << tp.location_
                << ": unterminated string (l.207): '"
                << misc::escape(yytext) << "'" << std::endl;
      BEGIN INITIAL;
  }

  . {
      grown_string += yytext;
  }
}


"class"     { CHECK_OBJECT();
              return TOKEN(CLASS); }

"extends"       { CHECK_OBJECT();
                  return TOKEN(EXTENDS); }

"method"    { CHECK_OBJECT();
              return TOKEN(METHOD); }

"if"        {return TOKEN(IF);}

"array"     {return TOKEN(ARRAY);}

"then"     {return TOKEN(THEN);}

"else"     {return TOKEN(ELSE);}

"while"     {return TOKEN(WHILE);}

"for"     {return TOKEN(FOR);}

"to"     {return TOKEN(TO);}

"do"     {return TOKEN(DO);}

"let"     {return TOKEN(LET);}

"in"     {return TOKEN(IN);}

"end"     {return TOKEN(END);}

"new"   { CHECK_OBJECT();
          return TOKEN(NEW); }

"of"     {return TOKEN(OF);}

"break"     {return TOKEN(BREAK);}

"nil"     {return TOKEN(NIL);}

"function"     {return TOKEN(FUNCTION);}

"var"     {return TOKEN(VAR);}

"type"     {return TOKEN(TYPE);}

"import"     {return TOKEN(IMPORT);}

"("     {return TOKEN(LPAREN);}

")"     {return TOKEN(RPAREN);}

"["     {return TOKEN(LBRACK);}

"]"     {return TOKEN(RBRACK);}

"{"     {return TOKEN(LBRACE);}

"}"     {return TOKEN(RBRACE);}

","     {return TOKEN(COMMA);}

"."     {return TOKEN(DOT);}

":"     {return TOKEN(COLON);}

";"     {return TOKEN(SEMI);}

"+"     {return TOKEN(PLUS);}

"-"     {return TOKEN(MINUS);}

"*"     {return TOKEN(TIMES);}

"/"     {return TOKEN(DIVIDE);}

"="     {return TOKEN(EQ);}

"<>"     {return TOKEN(NE);}

"<"     {return TOKEN(LT);}

"<="     {return TOKEN(LE);}

">"     {return TOKEN(GT);}

">="     {return TOKEN(GE);}

"&"     {return TOKEN(AND);}

"|"     {return TOKEN(OR);}

":="     {return TOKEN(ASSIGN);}

"primitive"     {return TOKEN(PRIMITIVE);}


"_namety"       {
                    CHECK_EXTENSION();
                    return TOKEN(NAMETY); }

"_exp"          {
                    CHECK_EXTENSION();
                    return TOKEN(EXP); }

"_lvalue"       {
                    CHECK_EXTENSION();
                    return TOKEN(LVALUE); }

"_chunks"       {
                    CHECK_EXTENSION();
                    return TOKEN(CHUNKS); }

"_cast"         {
                    CHECK_EXTENSION();
                    return TOKEN(CAST); }



"\n\r"          {}
"\r\n"          {}
"\n"            {tp.location_.lines();}
"\r"            {}

" "             {}



{symbol}         {
                return TOKEN_VAL(ID, yytext);
             }

.            {
    tp.error_ << misc::error::error_type::scan
                    << tp.location_
                    << ": bad token (l.350): '"
                    << yytext << "'\n";

}
  /* FIXME: Some code was deleted here. */
%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
