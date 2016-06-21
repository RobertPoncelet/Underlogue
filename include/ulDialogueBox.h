#ifndef ULDIALOGUEBOX_H
#define ULDIALOGUEBOX_H

#include <ncursesw/ncurses.h>

#include <vector>
#include <iostream>
#include "dialogue.h"
#include "ulAssetManager.h"
#include "ulDBoxElement.h"
//#include "ulDialogueOption.h"
//#include "ulLabel.h"

enum CHOICE
{
    OPTION_1,
    OPTION_2
};

class ulDialogueBox
{
public:
    ulDialogueBox(const std::vector<dialogueLine> &newScript);
    ~ulDialogueBox();
    void show();
    void start();
    void drawBorder();
    void printHelp();

private:
    static void resize(int sig);
    void preloadAssets(const std::vector<dialogueLine> &branch);
    void processBranch(const std::vector<dialogueLine> &branch);
    CHOICE playLine(const dialogueLine &line);
    void slowPrint(WINDOW* window, std::string text, float speed);
    void slowPrintDialogue(const dialogueLine &line);
    void regenerateWindows(const dialogueLine &line);

    ulAssetManager assetManager;
    std::vector<dialogueLine> script;
    //static dialogueLine currentLine;//only needed for window resizing

    int textWidth, textHeight, textX, textY;
    int optionWidth, optionHeight, option1X, option2X, optionY;
    WINDOW *wAvatar, /**wDialogue,*/ *wOption1, *wOption2;
    ulDBoxElement wDialogue;

};

#endif // ULDIALOGUEBOX_H
