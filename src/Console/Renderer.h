#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>

using namespace std;

class Renderer {
public:
    // Move cursor to specified position on screen
    static void goTo(short x, short y);
    // Change text and background color
    static void changeTextColor(const string &bgColor, const string &textColor);
    // Draw a box with specified dimensions
    static void drawBox(int x, int y, int width, int height);
    // Get character at specific screen position
    static char getCharAtPosition(short x, short y);
    // Show or hide cursor
    static void setCursorAppearance(bool show);
};

#endif