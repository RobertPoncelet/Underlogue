//This code is adapted from Bison 3.0.2's Calc++ example

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {ul_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
# include <string>
class ul_driver;
}
// The parsing context.
%param { ul_driver& driver }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
# include "ul-driver.hh"
}
%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  COLON  ":"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  NEWLINE "\n"
;
%token <std::string> STRING "string"
%token <std::string> STRING_LITERAL "stringliteral"
//%token <int> NUMBER "number"
//%type  <int> exp
%printer { yyoutput << $$; } <*>;

%%

/*%start unit;
unit: assignments exp  { driver.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "string" ":=" exp { driver.variables[$1] = $3; };

%left "+" "-";
%left "*" "/";
exp:
  exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { std::swap ($$, $2); }
| "string"  { $$ = driver.variables[$1]; }
| "number"      { std::swap ($$, $1); };*/

%start script;
script: item_list                                           { std::cout << "Entire script" << std::endl; }

item_list:
	item_list item                                          { std::cout << "Item list" << std::endl; 
                                                              driver.script.push_back(driver.currentLine); }
	| item                                                  { std::cout << "Single item" << std::endl; 
                                                              driver.script.push_back(driver.currentLine); }
	| %empty                                                { std::cout << "Empty item list" << std::endl; }
	;
	
item:
	regular_line                                            { std::cout << "Regular line" << std::endl; 
                                                              driver.currentLine.hasOptions = false; 
                                                              driver.currentLine.option1 = ""; 
                                                              driver.currentLine.option2 = ""; }
	| branching_section                                     { std::cout << "Branching section" << std::endl; }
	;
	
branching_section:
	option_line option_list option_list                     { std::cout << "Branching section body" << std::endl; }
	;
	
regular_line:
	character_identifier COLON STRING_LITERAL				{ std::cout << "This character says: " << $3 << std::endl;
                                                              driver.currentLine.dialogue = $3; }
	| STRING_LITERAL										{ std::cout << "Message from no character: " << $1 << std::endl; }
	;
	
option_line:
	regular_line options                                    { std::cout << "Option line body" << std::endl; }
	;
	
option_list:
	STRING COLON LPAREN item_list RPAREN		            { std::cout << "End of option branch: " << $1 << std::endl; }
    ;
	
character_identifier:
	STRING LPAREN STRING RPAREN		                		{ std::cout << "Character is " << $1 << " expressing " << $3 << std::endl; 
                                                              driver.currentLine.character = $1; driver.currentLine.expression = $3; }
	| STRING												{ std::cout << "Character is " << $1 << std::endl; 
                                                              driver.currentLine.character = $1; driver.currentLine.expression = ""; }
    ;
	
options:
	LPAREN STRING SLASH STRING RPAREN	            		{ std::cout << "Option 1: " << $2 << " Option 2: " << $4 << std::endl; }
    ;

%%

void yy::ul_parser::error(const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
