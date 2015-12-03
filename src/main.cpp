#include <panel.h>
#include <ncursesw/ncurses.h>
#include <locale.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "ulScriptReader.h"

int main(int argc, char* argv[])
{	
	ulScriptReader script = ulScriptReader();
	script.parseArguments(argc, &argv[0]);
	
	WINDOW *my_wins[3];
	PANEL  *my_panels[3];
	int lines = 10, cols = 40, y = 2, x = 4, i;

	setlocale(LC_ALL,"");
	initscr();
	cbreak();
	noecho();

	/* Create windows for the panels */
	my_wins[0] = newwin(lines, cols, y, x);
	my_wins[1] = newwin(lines, cols, y + 1, x + 5);
	my_wins[2] = newwin(lines, cols, y + 2, x + 10);

	/* 
	 * Create borders around the windows so that you can see the effect
	 * of panels
	 */
	for(i = 0; i < 3; ++i)
		box(my_wins[i], 0, 0);

	/* Attach a panel to each window */ 	/* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */

	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	doupdate();

	std::string line;
    std::ifstream portrait ("art/alphys.txt");
    int lineNum = 0;

    if (portrait.is_open())
    {
        while ( getline (portrait,line) )
        {
            mvprintw(10 + lineNum,10, "%s", line.c_str());
            //mvaddstr(10 + lineNum,10,line.c_str());
            ++lineNum;
        }
        portrait.close();
    }
    else std::cout << "Unable to open file\n";
    
    /*for (int i = 0; i < argc; ++i)
    {
		mvprintw(10 + i, 30, "%s", argv[i]);
	}*/

    refresh();
    doupdate();
	
	getch();
	endwin();
	
	script.printScript();
}

