//This code is adapted from Bison 3.0.2's Calc++ example

#ifndef UL_DRIVER_HH
#define UL_DRIVER_HH
#include <string>
#include <map>
#include <vector>
#include "ul-parser.hh"
#include "dialogue.h"
// Tell Flex the lexer's prototype ...
#define YY_DECL \
  yy::ul_parser::symbol_type yylex (ul_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;
// Conducting the whole scanning and parsing of Calc++.
class ul_driver
{
public:
  ul_driver ();
  virtual ~ul_driver ();

  std::map<std::string, int> variables;
  
  std::vector<dialogueLine> script;
  dialogueLine currentLine;

  int result;
  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  // Whether parser traces should be generated.
  bool trace_parsing;
  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
  
  void printScript();
};
#endif // ! UL_DRIVER_HH
