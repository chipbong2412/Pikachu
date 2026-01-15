#include "Colors.h"

#include <cstdlib>
#include <fstream>

#include "Constants.h"

// Initialize static members
bool Colors::isDarkMode = false;
string Colors::txtMainText;
string Colors::txtCellBorder;
string Colors::txtLetter;
string Colors::txtHighlightLetter;
string Colors::txtPath;
string Colors::txtButtonDrawing;
string Colors::txtButtonText;
string Colors::txtButtonHighlightText;
string Colors::txtBlue;
string Colors::bgMainBg;
string Colors::bgCellCursor;
string Colors::bgCellSelected;
string Colors::bgCellCorrect;
string Colors::bgCellWrong;
string Colors::bgCellHint;
string Colors::bgButtonSelecting;
string Colors::bgTitle;

void Colors::loadSettings() {
    ifstream fin("settings.txt");
    if (fin.is_open()) {
        fin >> isDarkMode;
        fin.close();
    }
}

void Colors::setColors() {
    if (isDarkMode) {
        // Dark mode
        system("color 0f"); // black background

        // Text colors
        txtMainText = TEXT_WHITE;
        txtCellBorder = TEXT_YELLOW;
        txtLetter = TEXT_GREEN;
        txtHighlightLetter = TEXT_WHITE;
        txtPath = TEXT_GREEN;
        txtButtonDrawing = TEXT_WHITE;
        txtButtonText = TEXT_GREEN;
        txtButtonHighlightText = TEXT_WHITE;
        txtBlue = TEXT_LIGHT_BLUE;

        // Background colors
        bgMainBg = BG_BLACK;
        bgCellCursor = BG_CYAN;
        bgCellSelected = BG_ORANGE;
        bgCellCorrect = BG_GREEN;
        bgCellWrong = BG_RED;
        bgCellHint = BG_PURPLE;
        bgButtonSelecting = BG_CYAN;
        bgTitle = BG_CYAN;
    } else {
        // Light mode
        system("color f0"); // white background

        // Text colors
        txtMainText = TEXT_BLACK;
        txtCellBorder = TEXT_YELLOW;
        txtLetter = TEXT_GREEN;
        txtHighlightLetter = TEXT_WHITE;
        txtPath = TEXT_GREEN;
        txtButtonDrawing = TEXT_BLACK;
        txtButtonText = TEXT_GREEN;
        txtButtonHighlightText = TEXT_WHITE;
        txtBlue = TEXT_BLUE;

        // Background colors
        bgMainBg = BG_WHITE;
        bgCellCursor = BG_CYAN;
        bgCellSelected = BG_ORANGE;
        bgCellCorrect = BG_GREEN;
        bgCellWrong = BG_RED;
        bgCellHint = BG_PURPLE;
        bgButtonSelecting = BG_CYAN;
        bgTitle = BG_CYAN;
    }
}

bool Colors::getIsDarkMode() { return isDarkMode; }

void Colors::setDarkMode(bool darkMode) {
    isDarkMode = darkMode;
    setColors();
}