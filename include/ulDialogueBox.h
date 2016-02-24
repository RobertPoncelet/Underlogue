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
//#include "ulDialogueOption.h"
//#include "ulLabel.h"

// original stuff holy shit

class ulDialogueBox
{
public:
    ulDialogueBox(const std::vector<dialogueLine> &newScript);
    ~ulDialogueBox();
    void show();

private:
    ulAssetManager assetManager;
    std::vector<dialogueLine> script;

};

#endif // ULDIALOGUEBOX_H
