#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#undef byte
#endif

#include <fstream>
#include <string>

#include "Colors.h"

using namespace std;

class Console {
private:
    static HWND consoleWindow;
    static bool soundEnabled;
    static bool initialized;

    // Console setup
    // Initialize console system
    static void initialize();
    // Setup console properties and appearance
    static void setupConsole();

    // Window management
    // Set console window handle
    static void setConsoleWindow();
    // Disable maximize button on console window
    static void disableMaximizeConsole();
    // Disable mouse input in console
    static void disableMouseInput();
    // Set console window title
    static void setConsoleTitle();

    // Settings
    // Load settings from configuration file
    static void loadSettings();
    // Save settings to configuration file
    static void saveSettings();

public:
    // Sound
    // Play sound effect
    static void playSFX(int sound);
    // Check if sound is enabled
    static bool isSoundEnabled();
    // Enable or disable sound
    static void setSoundEnabled(bool enabled);

    // Initialize console system (call once at startup)
    static void init();
};

#endif