#include "ulDialogueBox.h"
//#include <panel.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
//#include <ncurses.h>

ulDialogueBox::ulDialogueBox(const std::vector<dialogueLine> &newScript) :
    assetManager("art/art.json"),
    script(newScript)
{
    setlocale(LC_ALL, "");
    initscr();
}

ulDialogueBox::~ulDialogueBox()
{
    endwin();			/* End curses mode		  */
}

void ulDialogueBox::show()
{
    printw(assetManager.get("Alphys", "Default").avatar[0].c_str());
    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
}
