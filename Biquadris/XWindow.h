#ifndef __XWINDOW_H__
#define __XWINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <memory>

class Xwindow {
    Display * d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[11];
    int width, height;
    
public:
    Xwindow(int width=750, int height=700);  // Constructor; displays the window.
    ~Xwindow();                              // Destructor; destroys the window.
    
    enum { White = 0, Black, Red, Green, Blue, Cyan, Yellow, Magenta,
        Orange, Brown, DarkGreen }; // Available colours.
    
    
    // Draws a string
    void drawString(int x, int y, std::string msg, int colour = Black);
  
    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);
    
    
    // Draws a line from (x1, y1) to (x2, y2)
    void drawLine(int x1, int y1, int x2, int y2);
    
    
private:
    void printMessage(int x, int y, const std::string& msg, int colour, XFontStruct& f);
};

#endif
