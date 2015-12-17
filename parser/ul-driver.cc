//This code is adapted from Bison 3.0.2's Calc++ example

#include "ul-driver.hh"
#include "ul-parser.hh"
#include <iostream>

ul_driver::ul_driver()
  : trace_scanning (false), trace_parsing (false)
{
//  variables["one"] = 1;
//  variables["two"] = 2;
}

ul_driver::~ul_driver()
{
}

int ul_driver::parse(const std::string &f)
{
  file = f;
  scan_begin();
  yy::ul_parser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  scan_end();
  return res;
}

void ul_driver::error(const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void ul_driver::error(const std::string& m)
{
  std::cerr << m << std::endl;
}

void ul_driver::printScript()
{
    for (std::vector<dialogueLine>::iterator it = script.begin(); it != script.end(); ++it)
    {
        std::cout<<"NEW LINE **********************"<<std::endl;
        std::cout<<"Character: "<<(*it).character<<std::endl;
        std::cout<<"Expression: "<<(*it).expression<<std::endl;
        std::cout<<"Dialogue: "<<(*it).dialogue<<std::endl;
        if ((*it).hasOptions)
        {
            std::cout<<"Option 1: "<<(*it).option1<<std::endl;
            std::cout<<"Option 2: "<<(*it).option2<<std::endl;
        }
    }
}
