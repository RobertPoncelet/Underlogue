%{ /* -*- C++ -*- */ 
//This code is adapted from Bison 3.0.2's Calc++ example
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "ul-driver.hh"
# include "ul-parser.hh"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;
%}
%option noyywrap nounput batch debug noinput
id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step ();
%}

{blank}+   loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();
"-"      return yy::ul_parser::make_MINUS(loc);
"+"      return yy::ul_parser::make_PLUS(loc);
"*"      return yy::ul_parser::make_STAR(loc);
"/"      return yy::ul_parser::make_SLASH(loc);
"("      return yy::ul_parser::make_LPAREN(loc);
")"      return yy::ul_parser::make_RPAREN(loc);
":="     return yy::ul_parser::make_ASSIGN(loc);


{int}      {
  errno = 0;
  long n = strtol (yytext, NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    driver.error (loc, "integer is out of range");
  return yy::ul_parser::make_NUMBER(n, loc);
}

{id}       return yy::ul_parser::make_IDENTIFIER(yytext, loc);
.          driver.error (loc, "invalid character");
<<EOF>>    return yy::ul_parser::make_END(loc);
%%

void
ul_driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}



void
ul_driver::scan_end ()
{
  fclose (yyin);
}

