%{
#include <iostream>
#include "underlogue.tab.h"
#define YY_DECL extern "C" int yylex()
%}
%%
[ \t\n]         ;
\(		{ yylval.sval = strdup(yytext); return OPEN_BRACKET; }
\)		{ yylval.sval = strdup(yytext); return CLOSE_BRACKET; }
\/		{ yylval.sval = strdup(yytext); return SLASH; }
:		{ yylval.sval = strdup(yytext); return COLON; }
\"(\\.|[^"])*\" { yylval.sval = strdup(yytext); return STRING_LITERAL; }
[a-zA-Z0-9]+    { yylval.sval = strdup(yytext); return STRING; }
.		;
%%
