//This code is adapted from Bison 3.0.2's Calc++ example

#line 11154 "./doc/bison.texi"
%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {ul_parser}
#line 11170 "./doc/bison.texi"
%define api.token.constructor
%define api.value.type variant
%define parse.assert
#line 11187 "./doc/bison.texi"
%code requires
{
# include <string>
class ul_driver;
}
#line 11201 "./doc/bison.texi"
// The parsing context.
%param { ul_driver& driver }
#line 11213 "./doc/bison.texi"
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
#line 11228 "./doc/bison.texi"
%define parse.trace
%define parse.error verbose
#line 11239 "./doc/bison.texi"
%code
{
# include "ul-driver.hh"
}
#line 11255 "./doc/bison.texi"
%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  ASSIGN  ":="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
;
#line 11275 "./doc/bison.texi"
%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%type  <int> exp
#line 11288 "./doc/bison.texi"
%printer { yyoutput << $$; } <*>;
#line 11297 "./doc/bison.texi"
%%
%start unit;
unit: assignments exp  { driver.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" ":=" exp { driver.variables[$1] = $3; };

%left "+" "-";
%left "*" "/";
exp:
  exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { std::swap ($$, $2); }
| "identifier"  { $$ = driver.variables[$1]; }
| "number"      { std::swap ($$, $1); };
%%
#line 11327 "./doc/bison.texi"
void
yy::ul_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
