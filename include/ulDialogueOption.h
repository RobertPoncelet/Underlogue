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

class UserData
{
private:
  int u;
public:
  UserData(int x) : u(x) {}
  int sleeptime() const { return u; }
};
//
// -------------------------------------------------------------------------
//
template<class T> class ulDialogueOption : public NCursesUserItem<T>
{
public:
  ulDialogueOption (const char* p_name,
            const T* p_UserData)
    : NCursesUserItem<T>(p_name, static_cast<const char*>(0), p_UserData)
  {}

  virtual ~ulDialogueOption() {}

  bool action() {
    //SillyDemo a;
    //a.run(NCursesUserItem<T>::UserData()->sleeptime());
    std::cout<<"arse\n";
    mvprintw(0,0,"piss");
    return FALSE;
  }
};

template class ulDialogueOption<UserData>;
template class NCURSES_IMPEXP NCursesUserItem<UserData>;

class QuitItem : public NCursesMenuItem
{
public:
  QuitItem() : NCursesMenuItem("Quit") {
  }

  bool action() {
    return TRUE;
  }
};

#endif // ULDIALOGUEOPTION_H
