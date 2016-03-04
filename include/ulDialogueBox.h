#ifndef ULDIALOGUEBOX_H
#define ULDIALOGUEBOX_H

#include <ncursesw/ncurses.h>

#include <vector>
#include <iostream>
#include "dialogue.h"
#include "ulAssetManager.h"
//#include "ulDialogueOption.h"
//#include "ulLabel.h"

enum CHOICE
{
    option1,
    option2
};

class ulDialogueBox
{
public:
    ulDialogueBox(const std::vector<dialogueLine> &newScript);
    ~ulDialogueBox();
    void show();
    void start();
    void drawBorder();

private:
    static void resize(int sig)
    {
        std::cout<<"resized"<<sig<<std::endl; // TODO: anything whatsoever
    }
    void preloadAssets(const std::vector<dialogueLine> &branch);
    void processBranch(const std::vector<dialogueLine> &branch);
    CHOICE playLine(const dialogueLine &line);
    void slowPrint(WINDOW* window, std::string text, float speed);
    void regenerateWindows(const dialogueLine &line);
    void handleResize();

    ulAssetManager assetManager;
    std::vector<dialogueLine> script;
    //int wWidth;
    //int wHeight;

    int textWidth, textHeight, textX, textY;
    int optionWidth, optionHeight, option1X, option2X, optionY;
    WINDOW *wAvatar, *wText, *wOption1, *wOption2;

};

#endif // ULDIALOGUEBOX_H
