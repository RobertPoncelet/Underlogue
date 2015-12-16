//This code is adapted from Bison 3.0.2's Calc++ example

#line 11014 "./doc/bison.texi"
#ifndef UL_DRIVER_HH
# define UL_DRIVER_HH
# include <string>
# include <map>
# include "ul-parser.hh"
#line 11030 "./doc/bison.texi"
// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::ul_parser::symbol_type yylex (ul_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;
#line 11043 "./doc/bison.texi"
// Conducting the whole scanning and parsing of Calc++.
class ul_driver
{
public:
  ul_driver ();
  virtual ~ul_driver ();

  std::map<std::string, int> variables;

  int result;
#line 11061 "./doc/bison.texi"
  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
#line 11072 "./doc/bison.texi"
  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  // Whether parser traces should be generated.
  bool trace_parsing;
#line 11090 "./doc/bison.texi"
  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
};
#endif // ! UL_DRIVER_HH
