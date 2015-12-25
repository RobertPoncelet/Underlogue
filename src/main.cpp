#include <panel.h>
#include <ncursesw/ncurses.h>
#include <locale.h>

#include <iostream>
#include <fstream>
#include <sstream>

//#include "ulScriptReader.h"
#include "ul-driver.hh"

int main(int argc, char* argv[])
{	
    ul_driver driver;
  
    for (int i = 1; i < argc; ++i)
    {
	if (argv[i] == std::string("-p"))
	{
	    driver.trace_parsing = true;
	}
	else if (argv[i] == std::string("-s"))
	{
	    driver.trace_scanning = true;
	}
	else if (!driver.parse(argv[i]))
	{
	    std::cout << driver.result << std::endl;
	}
	else
	{
	    std::cout<<"Please supply a file path"<<std::endl;
	    return EXIT_FAILURE;
	}
    }
      
    driver.printScript(&driver.script);

    return EXIT_SUCCESS;
}

