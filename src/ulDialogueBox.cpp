#include "ulDialogueBox.h"
//#include <panel.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include <csignal>

ulDialogueBox::ulDialogueBox(const std::vector<dialogueLine> &newScript) :
    assetManager("art/art.json"),
    script(newScript)
{
}

ulDialogueBox::~ulDialogueBox()
{
    endwin();			/* End curses mode		  */
}

void ulDialogueBox::start()
{
    preloadAssets(script);

    //signal(SIGWINCH, ulDialogueBox::resize);
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    processBranch(script);
}

/*void ulDialogueBox::show()
{
    drawBorder();
    refresh();
    getch();

    mvwaddstr(wAvatar,0,0,assetManager.get("Alphys", "Default").avatar[0].c_str());
    wrefresh(wAvatar);
    getch();

    mvwaddstr(wText,0,0,"What the fuck did you just fucking say about me, you little bitch? I’ll have you know I graduated top of my class in the Navy Seals, and I’ve been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I’m the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You’re fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that’s just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little “clever” comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn’t, you didn’t, and now you’re paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You’re fucking dead, kiddo.");
    wrefresh(wText);
    getch();
}*/

void ulDialogueBox::resize(int sig)
{
    std::cout<<"resized!\n"; // TODO: anything whatsoever
}

void ulDialogueBox::drawBorder()
{
    int y, x;
    getmaxyx(stdscr, y, x);

    for (int i = 0; i < y; ++i)
    {
        mvaddstr(i, 0, "\u2588");
        mvaddstr(i, x-1, "\u2588");
    }

    for (int i = 1; i < x-1; ++i)
    {
        mvaddstr(0, i, "\u2580");
        mvaddstr(y-1, i, "\u2584");
    }
}

void ulDialogueBox::regenerateWindows(const dialogueLine &line)
{
    int winHeight, winWidth;
    getmaxyx(stdscr, winHeight, winWidth);

    // Avatar is placed one cell from the left border horizontally, centred vertically
    // We need to find its dimensions
    int avWidth = 50, avHeight = 0, lineLength = 0;
    auto lineA = assetManager.get(line.character, "Default");
    std::string frame = lineA.avatar[0];

    if (frame != "")
    {
        for (int i = 0; i < (int)frame.length(); ++i)
        {
            ++lineLength;

            if (frame[i] == '\n')
            {
                //TODO: make width work properly
                /*if (lineLength > avWidth)
                {
                    avWidth = lineLength;
                    std::cout<<"new line length: "<<lineLength<<std::endl
                }

                lineLength = 0;*/
                ++avHeight;
            }
        }
    }
    else
    {
        avWidth = 0;
        avHeight = 0;
    }

    //std::cout<<"width: "<<avWidth<<" height: "<<avHeight<<std::endl;

    wAvatar = newwin(avHeight, avWidth, (winHeight/2) - (avHeight/2), 2);

    // Horizontally: avatar ends, then an empty cell, then the * starting the dialogue,
    // then another empty cell, then the text window begins. It ends one cell before the
    //right border

    textWidth = winWidth - avWidth - 6;
    textHeight = avHeight/2;
    textX = avWidth + 2;
    textY = (winHeight/2) - (avHeight/2);

    if (line.hasOptions)
    {
        optionWidth = (textWidth/2) - 2;
        optionHeight = avHeight/2;
        option1X = textX;
        option2X = option1X + optionWidth + 3; //make room for the heart and empty cells either side
        optionY = winHeight / 2;

        wText = newwin(textHeight, textWidth, textY, textX);
        wOption1 = newwin(optionHeight, optionWidth, optionY, option1X);
        wOption2 = newwin(optionHeight, optionWidth, optionY, option2X);
    }
    else
    {
        wText = newwin(avHeight, textWidth, (winHeight/2) - (avHeight/2), avWidth + 2);
        wOption1 = newwin(0,0,0,0);
        wOption2 = newwin(0,0,0,0);
    }
}

void ulDialogueBox::preloadAssets(const std::vector<dialogueLine> &branch)
{
    for (dialogueLine line : branch)
    {
        assetManager.preload(line.character, line.expression);

        if (line.hasOptions)
        {
            preloadAssets(line.branch1);
            preloadAssets(line.branch2);
        }
    }
}

void ulDialogueBox::processBranch(const std::vector<dialogueLine> &branch)
{
    for (dialogueLine line : branch)
    {
        CHOICE choice = playLine(line);

        if (line.hasOptions)
        {
            if (choice == option1)
            {
                processBranch(line.branch1);
            }
            else
            {
                processBranch(line.branch2);
            }
        }
    }
}

CHOICE ulDialogueBox::playLine(const dialogueLine &line)
{
    //std::cout<<"char: "<<line.character
    //         <<" exp: "<<line.expression
    //         <<" dia: "<<line.dialogue
    //         <<std::endl;
    regenerateWindows(line);

    drawBorder();
    refresh();

    mvwaddstr(wAvatar,0,0,assetManager.get(line.character, line.expression).avatar[0].c_str());
    wrefresh(wAvatar);

    mvwaddstr(wText,0,0,line.dialogue.c_str());
    wrefresh(wText);
    getch();

    return option1;
}

