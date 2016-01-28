#ifndef ULDIALOGUEOPTION_H
#define ULDIALOGUEOPTION_H

#include "cursesapp.h"
#include "cursesm.h"
#include "cursesf.h"

#include <iostream>

/*enum ulDialogueOptionType
{
    optionA,
    optionB
};*/

/*class ulDialogueOptionData
{
private:
  int u;
public:
  ulDialogueOptionData(int x) : u(x) {}
  int sleeptime() const { return u; }
};*/


/*template<ulDialogueOptionType> class ulDialogueOption : public NCursesUserItem<ulDialogueOptionType>
{
public:
  ulDialogueOption (const char* p_name, const ulDialogueOptionType choice)
    : NCursesUserItem<ulDialogueOptionType>(p_name, static_cast<const char*>(0), choice)
  {}

  virtual ~ulDialogueOption() {}

  bool action()
  {
    std::cout<<"it's hip to fuck bees"<<std::endl;
    if (choice == optionA)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
  }

private:
  ulDialogueOptionType choice;
};

template class ulDialogueOption<ulDialogueOptionType>;
template class NCURSES_IMPEXP NCursesUserItem<ulDialogueOptionType>;*/

#endif // ULDIALOGUEOPTION_H
