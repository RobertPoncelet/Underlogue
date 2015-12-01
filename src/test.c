#include <ncursesw/ncurses.h>
#include <locale.h>
int main(int argc, char *argv[])
{
  setlocale(LC_ALL,"");
  initscr();
  curs_set(0); //remove cursor
  addstr("\u2588"); //Print out the unicode character
  refresh(); //update screen
  getch();  //wait for input
  endwin();
  return 0;
}