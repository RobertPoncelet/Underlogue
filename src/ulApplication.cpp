//#include <ncurses_cfg.h>
//#include <nc_string.h>
#include <iostream>

#include "ulDialogueBox.h"
#include "ulApplication.h"

void ulApplication::init_labels(Soft_Label_Key_Set& S) const
{
  for(int i=1; i <= S.labels(); i++)
  {
    char buf[8];
    assert(i < 100);
    snprintf(buf, NCURSES_CAST(size_t,sizeof(buf)), "Key%02d", i);
    S[i] = buf;                                      // Text
    S[i] = Soft_Label_Key_Set::Soft_Label_Key::Left; // Justification
  }
}

void ulApplication::title()
{
  const char * const titleText = "Simple C++ Binding Demo";
  const int len = ::strlen(titleText);

  titleWindow->bkgd(screen_titles());
  titleWindow->addstr(0, (titleWindow->cols() - len)/2, titleText);
  titleWindow->noutrefresh();
}


int ulApplication::run()
{
  ulDialogueBox M;
  M();
  return 0;
}

static ulApplication *Demo = new ulApplication();
