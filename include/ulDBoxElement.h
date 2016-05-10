#ifndef ULDBOXELEMENT_H
#define ULDBOXELEMENT_H

#include <string>
#include <locale.h>
#include <ncursesw/ncurses.h>

class ulDBoxElement
{
public:
    ulDBoxElement();
    ~ulDBoxElement();

    // Dimensions
    void setBoxExtent(int top, int bottom, int left, int right);
    void autoSizeByContent(bool heightOnly = true, bool aboutCentre = true);
    void setLeft(int left)          { setBoxExtent(getTop(), getBottom(), left, getRight()); }
    void setRight(int right)        { setBoxExtent(getTop(), getBottom(), getLeft(), right); }
    void setTop(int top)            { setBoxExtent(top, getBottom(), getLeft(), getRight()); }
    void setBottom(int bottom)      { setBoxExtent(getTop(), bottom, getLeft(), getRight()); }
    void setCentre(int y, int x);

    int getLeft() const     ;//{ return window ? window->_begx : -1; }
    int getRight() const    ;//{ return window ? window->_maxx : -1; }
    int getTop() const      ;//{ return window ? window->_begy : -1; }
    int getBottom() const   ;//{ return window ? window->_maxy : -1; }
    int getCentreX() const  ;//{ return window ? (window->_maxx + window->_begx) / 2 : -1; }
    int getCentreY() const  ;//{ return window ? (window->_maxy + window->_begy) / 2 : -1; }
    int getWidth() const    ;//{ return window ? (window->_maxx - window->_begx) / 2 : -1; }
    int getHeight() const   ;//{ return window ? (window->_maxy - window->_begy) / 2 : -1; }

    // Interactivity
    virtual bool step(); // Returns false if finished
    virtual void skip();
    virtual void reset();
    void refresh(bool clear = false);

    // Content
    void setContent(std::string inContent, bool shouldReset = true);

private:
    std::string content;
    std::string lineWrap(std::string inString, int lineWidth) const;
    int contentWidth(std::string inString) const;
    int contentHeight(std::string inString) const;

    int currentStep;

    WINDOW* window;
};

#endif // ULDBOXELEMENT_H
