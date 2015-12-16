%{
#include <cstdio>
#include <iostream>
//using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
//extern int lineNum;
 
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
item_list:
	item_list item
	| item
	| 
	;
	
item:
	regular_line
	| branching_section
	;
	
branching_section:
	option_line option_list option_list
	;
	
regular_line:
	character_identifier COLON STRING_LITERAL				{ std::cout << "This character says: " << $3 << std::endl; }
	| STRING_LITERAL										{ std::cout << "Message from no character: " << $1 << std::endl; }
	;
	
option_line:
	regular_line options
	;
	
option_list:
	STRING COLON OPEN_BRACKET item_list CLOSE_BRACKET		{ std::cout << "End of option branch: " << $1 << std::endl; }
	
character_identifier:
	STRING OPEN_BRACKET STRING CLOSE_BRACKET				{ std::cout << "Character is " << $1 << " expressing " << $3 << std::endl; }
	| STRING												{ std::cout << "Character is " << $1 << std::endl; }
	
options:
	OPEN_BRACKET STRING SLASH STRING CLOSE_BRACKET			{ std::cout << "Option 1: " << $2 << " Option 2: " << $4 << std::endl; }

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
	std::cout << "Parse error!  Message: " << s << std::endl;
	// might as well halt now:
	exit(-1);
}
