#ifndef ULDIALOGUEBOX_H
#define ULDIALOGUEBOX_H

#include <vector>
#include "dialogue.h"
#include "ulAssetManager.h"

class ulDialogueBox
{
public:
    ulDialogueBox();

private:
    ulAssetManager assetManager;
    std::vector<dialogueLine> script;

};

#endif // ULDIALOGUEBOX_H
