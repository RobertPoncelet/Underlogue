#ifndef ULLABEL_H
#define ULLABEL_H

//#include "internal.h"
#include "cursesapp.h"
#include "cursesm.h"
#include "cursesf.h"

class ulLabel : public NCursesFormField
{
public:
  ulLabel(const char* title,
        int row, int col)
    : NCursesFormField(1, static_cast<int>(::strlen(title)), row, col) {
      set_value(title);
      options_off(O_EDIT|O_ACTIVE);
  }
};

#endif // ULLABEL_H
