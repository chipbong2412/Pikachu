#include "Menu.h"

#include <windows.h>

#include <iostream>

using namespace std;

Menu::Menu()
    : title(nullptr), title_height(0), title_width(0), player_selection(""),
      highscores() {}

Menu::~Menu() { delete[] title; }

void Menu::loadTitle() {
    title_height = 0;
    title_width = 0;
    string line;
    ifstream fin;

    // read title dimension
    fin.open("assets\\title.txt");
    while (getline(fin, line)) {
        title_height++;
        if (line.length() > title_width)
            title_width = line.length();
    }
    fin.close();

    // read title
    fin.open("assets\\title.txt");
    title = new string[title_height];
    for (int i = 0; i < title_height; i++) {
        getline(fin, title[i]);
    }
    fin.close();
}

void Menu::displayTitle() {
    string line;
    for (int i = 0; i < title_height; i++) {
        Renderer::goTo(title_x, title_y + i);
        line = title[i];
        for (int j = 0; j < line.length(); j++) {
            if (line[j] != '#') {
                Renderer::changeTextColor(Colors::bgMainBg,
                                          Colors::txtMainText);
                cout << line[j];
            } else {
                Renderer::changeTextColor(Colors::bgTitle, Colors::txtMainText);
                cout << ' ';
            }
        }
        Renderer::changeTextColor(Colors::bgMainBg, Colors::bgMainBg);
    }
}

void Menu::startGame(int difficulty) {
    Game g(difficulty);
    g.initGame();
    g.gameLoop();
    displayTitle();
}

void Menu::showInfo() {
    Renderer::goTo(25, 19);
    cout << "Welcome to ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_YELLOW);
    cout << "Pikachu++";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ", a matching game on console. ";
    cout << "This is a project for Object-Oriented Programming course at ";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    cout << "physics@HCMUS";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ".";

    Renderer::goTo(25, 21);
    cout << "This project is made by ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
    cout << "Le Ha Thanh Hai";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ", ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
    cout << "Nguyen Ngoc Hai Anh";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ", ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
    cout << "Vu Nguyet Anh";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ", and ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
    cout << "Nguyen Thanh Quynh Giang";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ".";

    Renderer::goTo(25, 22);
    cout << "Under the instruction of ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_ORANGE);
    cout << "MSc. Nguyen Vuong Thuy Ngan";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << ".";

    Renderer::goTo(25, 24);
    cout << "Special thanks to ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
    cout << "Phung Ngoc Tuan";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << " and ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
    cout << "Ngo Quang Thang";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << " at";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    cout << " fit@HCMUS";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << " for discussions during game development.";

    Renderer::goTo(70, 28);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_PINK);
    cout << "Press ESC to go back to the main menu";
    while (InputHandler::getInput() != Input::ESCAPE)
        ;

    // clean up
    Renderer::goTo(25, 19);
    cout << string(150, ' ');
    Renderer::goTo(25, 21);
    cout << string(150, ' ');
    Renderer::goTo(25, 22);
    cout << string(150, ' ');
    Renderer::goTo(25, 24);
    cout << string(150, ' ');
    Renderer::goTo(70, 28);
    cout << string(150, ' ');
}

void Menu::showSetting() {
    const string setting_options[3]{"Theme", "Sound", "Back"};
    const string setting_instruction =
        "Set your preferences, please restart game for this to take effect";
    OptionsList setting_menu(setting_instruction, setting_options, 3, list_x,
                             list_y);

    const string theme_options[2]{"Light", "Dark"};
    OptionsList theme_menu("Set theme", theme_options, 2, list_x, list_y);
    const string sound_options[2]{"On", "Off"};
    OptionsList sound_menu("Set sound on/off", sound_options, 2, list_x,
                           list_y);

    bool is_dark_mode, is_sound_on;
    ifstream fin("settings.txt");
    fin >> is_dark_mode >> is_sound_on;
    fin.close();

    player_selection = setting_menu.selectOption();
    while (player_selection != "Back") {
        if (player_selection == "Theme") {
            player_selection = theme_menu.selectOption();
            if (player_selection == "Light")
                is_dark_mode = false;
            else if (player_selection == "Dark")
                is_dark_mode = true;
            player_selection = "";
        }

        else if (player_selection == "Sound") {
            player_selection = sound_menu.selectOption();
            if (player_selection == "On")
                is_sound_on = true;
            else if (player_selection == "Off")
                is_sound_on = false;
            player_selection = "";
        }
        player_selection = setting_menu.selectOption();
    }

    ofstream fout("settings.txt");
    fout << is_dark_mode << " " << is_sound_on;
    fout.close();
}

void Menu::startMenu() {
    const string main_menu_options[5]{"Play", "Highscores", "Infos", "Settings",
                                      "Quit Game"};
    const string difficulty_options[4]{"Easy", "Medium", "Hard", "Back"};
    const string quit_confirm[2]{"Yes", "No"};

    const string menu_instruction = "Press W/S to navigate, ENTER to select";
    const string difficulty_instruction = "Choose difficulty:";
    const string quit_instruction = "Quit game?";

    OptionsList main_menu(menu_instruction, main_menu_options, 5, list_x,
                          list_y);
    OptionsList difficulty_menu(difficulty_instruction, difficulty_options, 4,
                                list_x, list_y);
    OptionsList quit_menu(quit_instruction, quit_confirm, 2, list_x, list_y);

    loadTitle();
    displayTitle();

    while (true) {
        player_selection = main_menu.selectOption();

        if (player_selection == "Play") {
            player_selection = difficulty_menu.selectOption();

            if (player_selection == "Back") {
                player_selection = "";
                continue;
            }

            if (player_selection == "Easy") {
                player_selection = "";
                startGame(EASY);
                continue;
            }

            if (player_selection == "Medium") {
                player_selection = "";
                startGame(MEDIUM);
                continue;
            }

            if (player_selection == "Hard") {
                player_selection = "";
                startGame(HARD);
                continue;
            }
        }

        else if (player_selection == "Highscores") {
            player_selection = "";
            highscores.loadHighscores();
            highscores.displayHighscores();
            continue;
        }

        else if (player_selection == "Infos") {
            player_selection = "";
            showInfo();
            continue;
        }

        else if (player_selection == "Settings") {
            showSetting();
            player_selection = "";
            continue;
        }

        else if (player_selection == "Quit Game") {
            player_selection = quit_menu.selectOption();

            if (player_selection == "Yes") {
                player_selection = "";
                system("cls");
                break;
            }

            else if (player_selection == "No") {
                continue;
            }
        }
    }
}