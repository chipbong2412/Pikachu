#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "../Console/Colors.h"

using namespace std;

class Button {
private:
    string option;
    int x, y; // top left position of the button on screen

public:
    static const int width = 25;
    static const int height = 3; // size of the button

    Button() = default;
    Button(const string &opt, int pos_x, int pos_y);

    // Display the button with border and text
    void displayButton();
    // Highlight the button with specified colors
    void
    highlightButton(const string &bg_color = Colors::bgButtonSelecting,
                    const string &text_color = Colors::txtButtonHighlightText);
    // Remove highlight from the button
    void unhighlightButton();
    // Remove the button from screen
    void removeButton();

    // Getters
    string getOption() const { return option; }
    int getX() const { return x; }
    int getY() const { return y; }

    // Setters
    void setOption(const string &opt) { option = opt; }
    void setPosition(int pos_x, int pos_y) {
        x = pos_x;
        y = pos_y;
    }
};

#endif