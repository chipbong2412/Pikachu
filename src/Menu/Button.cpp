#include "Button.h"

#include <iostream>

#include "../Console/Renderer.h"

using namespace std;

Button::Button(const string &opt, int pos_x, int pos_y)
    : option(opt), x(pos_x), y(pos_y) {}

void Button::displayButton() {
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtButtonDrawing);
    Renderer::drawBox(x, y, width, height);

    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtButtonText);
    int len = option.length();
    Renderer::goTo(x + (width - len) / 2, y + height / 2);
    cout << option;
}

void Button::highlightButton(const string &bg_color, const string &text_color) {
    Renderer::changeTextColor(bg_color, text_color);
    for (int i = 1; i < height - 1; i++) {
        Renderer::goTo(x + 1, y + i);
        cout << string(width - 2, ' ');
    }
    int len = option.length();
    Renderer::goTo(x + (width - len) / 2, y + height / 2);
    cout << option;
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
}

void Button::unhighlightButton() {
    highlightButton(Colors::bgMainBg, Colors::txtButtonText);
}

void Button::removeButton() {
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    for (int i = 0; i < height; i++) {
        Renderer::goTo(x, y + i);
        cout << string(width, ' ');
    }
}