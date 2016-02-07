#include "ulDialogueBox.h"

ulDialogueBox::ulDialogueBox()
  : NCursesMenu (n_items+2, 8, (lines()-10)/2, (cols()-10)/2),
    P(0), I(0), u(0)
{
  u = new UserData(1);
  I = new NCursesMenuItem*[1+n_items];
  //I[0] = new MyAction("Option A", "something");
  //I[1] = new MyAction("Option B", "something else");
  I[0] = new ulDialogueOption<UserData> ("Silly", u);
  I[1] = new QuitItem();
  I[2] = new NCursesMenuItem(); // Terminating empty item

  InitMenu(I, TRUE, TRUE);

  mvprintw(1, 0, "fuck");

  P = new NCursesPanel(1, n_items, LINES-1, 1);
  boldframe("oh", "shit");
  //P->show();
}

ulDialogueBox& ulDialogueBox::operator=(const ulDialogueBox& rhs)
{
  if (this != &rhs) {
    *this = rhs;
  }
  return *this;
}

ulDialogueBox::ulDialogueBox(const ulDialogueBox& rhs)
  : NCursesMenu(rhs), P(0), I(0), u(0)
{
}

ulDialogueBox::~ulDialogueBox()
{
  P->hide();
  delete P;
  delete u;
}

void ulDialogueBox::On_Menu_Init()
{
  NCursesWindow W(::stdscr);
  P->move(0, 0);
  P->clrtoeol();
  for(int i=1; i<count(); i++)
    P->addch('#');
  P->bkgd(W.getbkgd());
  refresh();
}

void ulDialogueBox::On_Menu_Termination()
{
  P->move(0, 0);
  P->clrtoeol();
  refresh();
}

void ulDialogueBox::On_Item_Init(NCursesMenuItem& item)
{
  P->move(0, item.index());
  P->attron(A_REVERSE);
  P->printw("%1d", 1+item.index());
  P->attroff(A_REVERSE);
  refresh();
}

void ulDialogueBox::On_Item_Termination(NCursesMenuItem& item)
{
  P->move(0, item.index());
  P->attroff(A_REVERSE);
  P->printw("%1d", 1+item.index());
  refresh();
}
