#include <panel.h>
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <ncurses.h>

#include <iostream>
#include <fstream>
#include <sstream>

//#include "ulScriptReader.h"
#include "ul-driver.hh"
#include "ulAssetManager.h"
#include "ulApplication.h"

/*int main(int argc, char* argv[])
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

    ulAssetManager assMan; // oh yes bby~
    lineAsset ass = assMan.get("Alphys", "");
    std::cout<<ass.avatar[0];
    lineAsset invalidAss = assMan.get("i don't exist", "lmao");

    ulApplication *app = new ulApplication;
    app->run();
    delete app;

    return EXIT_SUCCESS;
}*/

