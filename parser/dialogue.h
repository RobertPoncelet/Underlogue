#ifndef DIALOGUE_HH
#define DIALOGUE_HH
#include <string>

//typedef std::vector<dialogueLine> dialogueBranch;

struct dialogueLine
{
    std::string character;
    std::string expression;
    std::string dialogue;
    bool hasOptions;
    std::string option1;
    std::string option2;
    std::vector<dialogueLine> branch1;
    std::vector<dialogueLine> branch2;
};

#endif
