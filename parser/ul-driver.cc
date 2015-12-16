//This code is adapted from Bison 3.0.2's Calc++ example

#line 11104 "./doc/bison.texi"
#include "ul-driver.hh"
#include "ul-parser.hh"

ul_driver::ul_driver ()
  : trace_scanning (false), trace_parsing (false)
{
  variables["one"] = 1;
  variables["two"] = 2;
}

ul_driver::~ul_driver ()
{
}

int
ul_driver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::ul_parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

void
ul_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void
ul_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
