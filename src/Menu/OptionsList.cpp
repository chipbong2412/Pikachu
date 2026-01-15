#include "OptionsList.h"

#include <iostream>

#include "../Console/Renderer.h"

using namespace std;

OptionsList::OptionsList(const string &instruction, const string button_text[],
                         int n, int pos_x, int pos_y)
    : x(pos_x), y(pos_y), button_instruction(instruction),
      number_of_buttons(n) {
    button_arr = new Button[number_of_buttons];
    for (int i = 0; i < number_of_buttons; i++) {
        button_arr[i] = Button(button_text[i], x, y + 2 + Button::height * i);
    }
}

OptionsList::~OptionsList() { delete[] button_arr; }

void OptionsList::displayOptionsList() {
    int len = button_instruction.length();
    Renderer::goTo(x + (Button::width - len) / 2, y);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << button_instruction;

    for (int i = 0; i < number_of_buttons; i++) {
        button_arr[i].displayButton();
    }
}

void OptionsList::removeOptionsList() {
    int len = button_instruction.length();
    Renderer::goTo(x + (Button::width - len) / 2, y);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << string(len, ' ');

    for (int i = 0; i < number_of_buttons; i++) {
        button_arr[i].removeButton();
    }
}

string OptionsList::selectOption() {
    displayOptionsList();
    Input inp;
    int cur = 0;
    button_arr[cur].highlightButton();

    while (true) {
        inp = InputHandler::getInput();

        if (inp == Input::INVALID)
            continue;

        if (inp == Input::UP) {
            button_arr[cur].unhighlightButton();
            cur = (cur - 1 + number_of_buttons) % number_of_buttons;
            button_arr[cur].highlightButton();
        }

        else if (inp == Input::DOWN) {
            button_arr[cur].unhighlightButton();
            cur = (cur + 1) % number_of_buttons;
            button_arr[cur].highlightButton();
        }

        else if (inp == Input::ENTER) {
            Console::playSFX(SFX_SELECT);
            removeOptionsList();
            return button_arr[cur].getOption();
        }
    }
}