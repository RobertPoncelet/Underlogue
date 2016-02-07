#ifndef ULDIALOGUEBOX_H
#define ULDIALOGUEBOX_H

//#include "internal.h"
#include "cursesapp.h"
#include "cursesm.h"
#include "cursesf.h"

#include <vector>
#include <iostream>
#include "dialogue.h"
#include "ulAssetManager.h"
#include "ulDialogueOption.h"
#include "ulLabel.h"

class ulDialogueBox : public NCursesMenu
{
private:
  NCursesPanel* P;
  NCursesMenuItem** I;
  UserData *u;
  #define n_items 2

public:
  ulDialogueBox();
  ulDialogueBox& operator=(const ulDialogueBox& rhs);
  ulDialogueBox(const ulDialogueBox& rhs);
  ~ulDialogueBox();
  virtual void On_Menu_Init();
  virtual void On_Menu_Termination();
  virtual void On_Item_Init(NCursesMenuItem& item);
  virtual void On_Item_Termination(NCursesMenuItem& item);

// original stuff holy shit

private:
    ulAssetManager assetManager;
    std::vector<dialogueLine> script;

};

#endif // ULDIALOGUEBOX_H
