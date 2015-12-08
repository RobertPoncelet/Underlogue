%{
#include <cstdio>
#include <iostream>
//using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union 
{
	char *sval;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <sval> OPEN_BRACKET
%token <sval> CLOSE_BRACKET
%token <sval> SLASH
%token <sval> COLON
%token <sval> STRING
%token <sval> STRING_LITERAL

%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:
derp:
	OPEN_BRACKET derp      	 { std::cout << "bison found an open bracket: " << $1 << std::endl; }
	| CLOSE_BRACKET derp	 { std::cout << "bison found a close bracket: " << $1 << std::endl; }
	| SLASH derp	 	 { std::cout << "bison found a slash: " << $1 << std::endl; }
	| COLON derp           	 { std::cout << "bison found a colon: " << $1 << std::endl; }
	| STRING derp         	 { std::cout << "bison found a string: " << $1 << std::endl; }
	| STRING_LITERAL derp    { std::cout << "bison found a string literal: " << $1 << std::endl; }
	| OPEN_BRACKET      	 { std::cout << "bison found an open bracket: " << $1 << std::endl; }
	| CLOSE_BRACKET 	 { std::cout << "bison found a close bracket: " << $1 << std::endl; }
	| SLASH 	 	 { std::cout << "bison found a slash: " << $1 << std::endl; }
	| COLON            	 { std::cout << "bison found a colon: " << $1 << std::endl; }
	| STRING          	 { std::cout << "bison found a string: " << $1 << std::endl; }
	| STRING_LITERAL         { std::cout << "bison found a string literal: " << $1 << std::endl; }
	;
%%

int main(int, char**) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("scriptTest.txt", "r");
	// make sure it's valid:
	if (!myfile) {
		std::cout << "I can't open this file!" << std::endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	std::cout << "EEK, parse error!  Message: " << s << std::endl;
	// might as well halt now:
	exit(-1);
}
