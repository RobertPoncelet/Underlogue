#include "include/ulDBoxElement.h"

#include <iostream>

/*
#define IN_HEIGHT (bottom - top)
#define IN_WIDTH (right - left)
#define IN_CENTER_Y ((top + bottom) / 2)
#define IN_CENTER_X ((left + right) / 2)
*/

ulDBoxElement::ulDBoxElement() :
    content(std::string("")), currentStep(0)
{
    //setBoxExtent(top, bottom, left, right);
    window = newwin(0, 0, 0, 0);
    //setBoxExtent(top, bottom, left, right);
}

ulDBoxElement::~ulDBoxElement()
{
    delwin(window);
}

void ulDBoxElement::setBoxExtent(int top, int bottom, int left, int right)
{
    delwin(window);
    window = newwin(bottom-top, right-left, top, left);
    refresh();
}

void ulDBoxElement::autoSizeByContent(bool heightOnly, bool aboutCentre)
{
    if (heightOnly)
    {
        content = lineWrap(content, getWidth());
        int height = contentHeight(content);
        std::cout<<"height: "<<height<<std::endl;

        if (aboutCentre)
        {
            int halfHeight = std::max(1, height / 2);
            setBoxExtent(getCentreY() - halfHeight,
                         getCentreY() + (height - halfHeight), // Do this in case of uneven splits
                         getLeft(),
                         getRight());
        }
        else
        {
            setBoxExtent(getTop(),
                         getTop() + height,
                         getLeft(),
                         getRight());
        }
    }
    else
    {
        int height = contentHeight(content);
        int width = contentWidth(content);

        if (aboutCentre)
        {
            int halfHeight = height / 2;
            int halfWidth = width / 2;
            setBoxExtent(getCentreY() - halfHeight,
                         getCentreY() + (height - halfHeight), // Do this in case of uneven splits
                         getCentreX() - halfWidth,
                         getCentreX() + (width - halfWidth));
        }
        else
        {
            setBoxExtent(getTop(),
                         getTop() + height,
                         getLeft(),
                         getLeft() + width);
        }
    }
}

void ulDBoxElement::setCentre(int y, int x)
{
    int halfWidth = getWidth() / 2;
    int halfHeight = getHeight() / 2;
    setBoxExtent(y - halfHeight, y + halfHeight, x - halfWidth, x + halfWidth);
}

bool ulDBoxElement::step()
{
    ++currentStep;
    refresh();

    if (currentStep >= (int)content.length())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ulDBoxElement::skip()
{
    currentStep = -1;
    refresh();
}

void ulDBoxElement::reset()
{
    wclear(window);
    currentStep = 0;
    refresh();
}

void ulDBoxElement::refresh(bool clear)
{
    if (clear)
    {
        wclear(window);
    }
    if (currentStep >= 0 && currentStep < (int)content.length())
    {
        mvwaddstr(window, 0, 0, content.substr(0, currentStep).c_str());
    }
    else
    {
        mvwaddstr(window, 0, 0, content.c_str());
    }
    wrefresh(window);
}

void ulDBoxElement::setContent(std::string inContent, bool shouldReset)
{
    content = inContent;
    if (shouldReset)
    {
        reset();
    }
}

std::string ulDBoxElement::lineWrap(std::string inString, int lineWidth) const
{
    // This function is adapted from:
    // http://www.cprogramming.com/snippets/source-code/word-wrap-in-c

    /*
       This function takes a string and an output buffer and a desired width. It then copies
       the string to the buffer, inserting a new line character when a certain line
       length is reached.  If the end of the line is in the middle of a word, it will
       backtrack along the string until white space is found.
     */

    // TODO: fix
    /*int i = 0;
    int k, counter;
    std::string::iterator iterator;
    //char buffer[2 * inString.length()];
    std::string outString("");

    while(i < (int)inString.length() )
    {
        // copy string until the end of the line is reached
        for ( int iterator = 0; iterator <= lineWidth; ++iterator )
        {
            // check if end of string reached
            if ( i == (int)inString.length() )
            {
                //buffer[ i ] = 0;
                //return std::string(buffer);
                return outString;
            }
            //buffer[ i ] = inString[ i ];
            outString += inString[i];
            // check for newlines embedded in the original input
            // and reset the index
            //if ( buffer[ i ] == '\n' )
            if ( inString[i] == '\n' )
            {
                //counter = 1;
                iterator = 0;
            }
            ++i;
        }
        // check for whitespace
        if (inString[ i ] == ' ' || inString[ i ] == '\t' || inString[ i ] == '\n')
        {
            outString += '\n';
            ++i;
        }
        else
        {
            // check for nearest whitespace back in string
            for ( k = i; k > 0; k--)
            {
                if (inString[ k ] == ' ' || inString[ k ] == '\t' || inString[ k ] == '\n')
                {
                    //buffer[ k ] = '\n';
                    // set string index back to character after this one
                    i = k + 1;
                    break;
                }
            }
        }
    }

    return outString;*/

    // Adapted from http://alexrodgers.co.uk/2012/08/09/c-word-wrap-for-console-output-tutorial/

    for (unsigned int i = 1; i <= inString.length() ; i++)
    {
        if ((i % lineWidth) == 0)
        {
            int spaceCount = 0;
            if (inString[(i-1)] != ' ')
            {
                for (int j = (i-1); j > -1 ; j--)
                {
                    if (inString[j] == ' ')
                    {
                        inString.insert(j, spaceCount, ' ');
                        break;
                    }
                    else spaceCount++;
                }
            }
        }
    }

    return inString;
}

int ulDBoxElement::contentHeight(std::string inString) const
{
    int count = 1;
    for (char current : inString)
    {
        if (current == '\n')
        {
            ++count;
        }
    }
    return count;
}

int ulDBoxElement::contentWidth(std::string inString) const
{
    // This function is adapted from:
    // http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

    size_t pos = 0;
    int maxSize = 0;
    while ((pos = inString.find('\n')) != std::string::npos)
    {
        inString.erase(0, pos + 1);
        if ((int)pos > maxSize)
        {
            maxSize = (int)pos;
        }
    }

    return maxSize;
}

int ulDBoxElement::getLeft() const     { return window ? window->_begx : -1; }
int ulDBoxElement::getRight() const    { return window ? window->_maxx : -1; }
int ulDBoxElement::getTop() const      { return window ? window->_begy : -1; }
int ulDBoxElement::getBottom() const   { return window ? window->_maxy : -1; }
int ulDBoxElement::getCentreX() const  { return window ? (window->_maxx + window->_begx) / 2 : -1; }
int ulDBoxElement::getCentreY() const  { return window ? (window->_maxy + window->_begy) / 2 : -1; }
int ulDBoxElement::getWidth() const    { return window ? (window->_maxx - window->_begx) / 2 : -1; }
int ulDBoxElement::getHeight() const   { return window ? (window->_maxy - window->_begy) / 2 : -1; }
