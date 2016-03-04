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
script: item_list                                           { std::cout << "End of script" << std::endl; }

item_list:
	item_list item                                          { /*std::cout << "Item list" << std::endl;*/ 
                                                              //driver.addCurrentLineToScript();
                                                              /*driver.printLine(driver.currentLine);*/ }
	| item                                                  { /*std::cout << "Single item" << std::endl;*/ 
                                                              //driver.addCurrentLineToScript();
                                                              /*driver.printLine(driver.currentLine);*/ }
	| %empty                                                { std::cout << "Empty item list" << std::endl; }
	;
	
item:
	regular_line                                            { std::cout << "Regular line" << std::endl; 
                                                              driver.getCurrentLine().hasOptions = false; 
                                                              driver.getCurrentLine().option1 = ""; 
                                                              driver.getCurrentLine().option2 = ""; 
                                                              driver.popLineToScript(); }
	| branching_section                                     { std::cout << "End of branching section" << std::endl; 
                                                              driver.getCurrentLine().hasOptions = true;
                                                              driver.popLineToScript(); }
	;
	
branching_section:
	option_line option_list_1 option_list_2                 { /*std::cout << "Branching section body" << std::endl;*/ }
	;
	
regular_line:
	character_identifier COLON STRING_LITERAL				{ std::cout << "This character says: " << $3 << std::endl;
                                                              std::string dia = $3;
                                                              driver.getCurrentLine().dialogue = dia.substr(1, dia.length() - 2); }
	| STRING_LITERAL										{ std::cout << "Message from no character: " << $1 << std::endl;
                                                              driver.pushLine();
                                                              std::string dia = $1;
                                                              driver.getCurrentLine().dialogue = dia.substr(1, dia.length() - 2);
                                                              driver.getCurrentLine().character = "";
                                                              driver.getCurrentLine().expression = ""; }
	;
	
option_line:
	regular_line options                                    { /*std::cout << "Option line body" << std::endl;*/ }
	;
	
option_list_1:
	STRING COLON LPAREN item_list RPAREN		            { std::cout << "End of option branch 1" << std::endl; 
                                                              driver.switchToBranch2(); }
    ;
    
option_list_2:
	STRING COLON LPAREN item_list RPAREN		            { std::cout << "End of option branch 2" << std::endl; 
                                                              driver.popBranch(); }
    ;
	
character_identifier:
	STRING LPAREN STRING RPAREN		                		{ std::cout << "Character is " << $1 << " expressing " << $3 << std::endl;
                                                              driver.pushLine();
                                                              driver.getCurrentLine().character = $1;
                                                              driver.getCurrentLine().expression = $3; }
	| STRING												{ std::cout << "Character is " << $1 << std::endl; 
                                                              driver.pushLine();
                                                              driver.getCurrentLine().character = $1; driver.getCurrentLine().expression = ""; }
    ;
	
options:
	LPAREN STRING SLASH STRING RPAREN	            		{ std::cout << "Option 1: " << $2 << " Option 2: " << $4 << std::endl; 
                                                              driver.getCurrentLine().option1 = $2; driver.getCurrentLine().option2 = $4; 
                                                              driver.getCurrentLine().hasOptions = true;
                                                              driver.pushBranch(); }
    ;

%%

void yy::ul_parser::error(const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
