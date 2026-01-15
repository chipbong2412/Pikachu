#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <string>

#include "../Console/Colors.h"
#include "../Console/Constants.h"
#include "../Console/Renderer.h"
#include "../Game/Game.h"
#include "../Game/Highscores.h"
#include "OptionsList.h"

using namespace std;

class Menu {
private:
    static const int title_x = (CONSOLE_WIDTH - 76) / 2;
    static const int title_y = 5;
    static const int list_x = (CONSOLE_WIDTH - Button::width) / 2;
    static const int list_y = 17;

    string *title;
    int title_height;
    int title_width;
    string player_selection;
    Highscores highscores;

    // Load title from title.txt file
    void loadTitle();
    // Display the title on screen
    void displayTitle();
    // Start a new game with specified difficulty
    void startGame(int difficulty);
    // Show information about the game and developers
    void showInfo();
    // Show settings menu for theme and sound configuration
    void showSetting();

public:
    Menu();
    ~Menu();

    // Display main menu and handle navigation
    void startMenu();
};

#endif