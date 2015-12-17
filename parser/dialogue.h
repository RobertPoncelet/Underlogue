#ifndef DIALOGUE_HH
#define DIALOGUE_HH
#include <string>

struct dialogueLine
{
    std::string character;
    std::string expression;
    std::string dialogue;
    bool hasOptions;
    std::string option1;
    std::string option2;
    dialogueLine* nextLine1;
    dialogueLine* nextLine2;
};

#endif
