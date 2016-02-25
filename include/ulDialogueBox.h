#ifndef ULDIALOGUEBOX_H
#define ULDIALOGUEBOX_H

#include <ncursesw/ncurses.h>

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
    void start();
    void drawBorder();
    void regenerateWindows(const dialogueLine &line);

private:
    void resize(int sig);


    ulAssetManager assetManager;
    std::vector<dialogueLine> script;
    //int wWidth;
    //int wHeight;

    WINDOW* wAvatar;
    WINDOW* wText;
    WINDOW* wOption1;
    WINDOW* wOption2;

};

#endif // ULDIALOGUEBOX_H
