#ifndef ULAPPLICATION_H
#define ULAPPLICATION_H

//#include "internal.h"
#include "cursesapp.h"
#include "cursesm.h"
#include "cursesf.h"

class ulApplication : public NCursesApplication
{
protected:
  int titlesize() const { return 1; }
  void title();
  Soft_Label_Key_Set::Label_Layout useSLKs() const {
    return Soft_Label_Key_Set::PC_Style_With_Index;
  }
  void init_labels(Soft_Label_Key_Set& S) const;

public:
  ulApplication() : NCursesApplication(TRUE)
  {
  }

  int run();
};

#endif // ULAPPLICATION_H
