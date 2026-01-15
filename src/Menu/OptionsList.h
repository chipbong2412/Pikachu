#ifndef OPTIONSLIST_H
#define OPTIONSLIST_H

#include <string>

#include "../Console/Console.h"
#include "../Console/Constants.h"
#include "../Console/Input.h"
#include "Button.h"

using namespace std;

class OptionsList {
private:
    int x, y; // top left position of the list on screen
    int number_of_buttons;
    string button_instruction;
    Button *button_arr;

    // Display the instruction and all buttons in the list
    void displayOptionsList();

public:
    OptionsList(const string &instruction, const string button_text[], int n,
                int pos_x, int pos_y);
    ~OptionsList();

    // Remove the instruction and all buttons from screen
    void removeOptionsList();
    // Handle navigation and return selected option
    string selectOption();
};

#endif