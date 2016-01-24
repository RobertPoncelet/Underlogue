#ifndef ULDIALOGUEBOX_H
#define ULDIALOGUEBOX_H

//#include "internal.h"
#include "cursesapp.h"
#include "cursesm.h"
#include "cursesf.h"

#include <vector>
#include "dialogue.h"
#include "ulAssetManager.h"
#include "ulLabel.h"

class ulDialogueBox : public NCursesForm
{
private:
  NCursesFormField** F;
  //MyFieldType* mft;
  Integer_Field *ift;
  Enumeration_Field *eft;

  static const char *weekdays[];

public:
  ulDialogueBox()
    : NCursesForm(13, 51, (lines() - 15)/2, (cols() - 53)/2),
      F(0),
      //mft(0),
      ift(0),
      eft(0)
  {

    F     = new NCursesFormField*[10];
    //mft   = new MyFieldType('X');
    ift   = new Integer_Field(0, 1, 10);
    eft   = new Enumeration_Field(weekdays);

    F[0]  = new ulLabel("Demo Entry Form", 0, 16);
    F[1]  = new ulLabel("Weekday Enum", 2, 1);
    F[2]  = new ulLabel("Number(1-10)", 2, 21);
    F[3]  = new ulLabel("Only 'X'", 2, 35);
    F[4]  = new ulLabel("Multiline Field (Dynamic and Scrollable)", 5, 1);
    F[5]  = new NCursesFormField(1, 18, 3, 1);
    F[6]  = new NCursesFormField(1, 12, 3, 21);
    F[7]  = new NCursesFormField(1, 12, 3, 35);
    F[8]  = new NCursesFormField(4, 46, 6, 1, 2);
    F[9]  = new NCursesFormField();

    InitForm(F, TRUE, TRUE);
    boldframe();

    F[5]->set_fieldtype(*eft);
    F[6]->set_fieldtype(*ift);

//    F[7]->set_fieldtype(*mft);
//    F[7]->set_maximum_growth(20); // max. 20 characters
//    F[7]->options_off(O_STATIC);  // make field dynamic

    F[7]->set_maximum_growth(10); // max. 10 lines
    F[7]->options_off(O_STATIC);  // make field dynamic
  }

  ulDialogueBox& operator=(const ulDialogueBox& rhs)
  {
    if (this != &rhs) {
      *this = rhs;
    }
    return *this;
  }

  ulDialogueBox(const ulDialogueBox& rhs)
    : NCursesForm(rhs), F(0), /*mft(0),*/ ift(0), eft(0)
  {
  }

  ~ulDialogueBox() {
    //delete mft;
    delete ift;
    delete eft;
  }

// original stuff holy shit

private:
    ulAssetManager assetManager;
    std::vector<dialogueLine> script;

};

#endif // ULDIALOGUEBOX_H
