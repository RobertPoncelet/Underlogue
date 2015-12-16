%{
#include <iostream>
#include "underlogue.tab.h"
#define YY_DECL extern "C" int yylex()
int lineNum = 1;
%}
%%
[ \t]           ;
\(		{ return OPEN_BRACKET; }
\)		{ return CLOSE_BRACKET; }
\/		{ return SLASH; }
:		{ return COLON; }
\"(\\.|[^"])*\"	{ yylval.sval = strdup(yytext); return STRING_LITERAL; }
[a-zA-Z0-9]+    { yylval.sval = strdup(yytext); return STRING; }
\n		{ /*++lineNum;*/ return NEWLINE; }
.		;
%%
