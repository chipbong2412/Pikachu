#ifndef COLORS_H
#define COLORS_H

#include <string>

using namespace std;

class Colors {
private:
    static bool isDarkMode;

public:
    // Text colors
    static string txtMainText;
    static string txtCellBorder;
    static string txtLetter;
    static string txtHighlightLetter;
    static string txtPath;
    static string txtButtonDrawing;
    static string txtButtonText;
    static string txtButtonHighlightText;
    static string txtBlue;

    // Background colors
    static string bgMainBg;
    static string bgCellCursor;
    static string bgCellSelected;
    static string bgCellCorrect;
    static string bgCellWrong;
    static string bgCellHint;
    static string bgButtonSelecting;
    static string bgTitle;

public:
    // Load color settings from configuration
    static void loadSettings();
    // Set color scheme based on dark/light mode
    static void setColors();
    // Get current dark mode status
    static bool getIsDarkMode();
    // Set dark mode on or off
    static void setDarkMode(bool darkMode);
};

#endif