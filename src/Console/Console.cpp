#include "Console.h"

#include "Constants.h"
#include "Renderer.h"

// Initialize static members
HWND Console::consoleWindow = GetConsoleWindow();
bool Console::soundEnabled = true;
bool Console::initialized = false;

void Console::init() {
    if (!initialized) {
        initialize();
        initialized = true;
    }
}

void Console::initialize() {
    loadSettings();
    setupConsole();
}

void Console::setupConsole() {
    setConsoleWindow();
    disableMouseInput();
    disableMaximizeConsole();
    setConsoleTitle();
    Renderer::setCursorAppearance(false); // hide console cursor
}

void Console::setConsoleWindow() {
    MoveWindow(consoleWindow, 100, 50, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
}

void Console::disableMaximizeConsole() {
    DWORD style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console::disableMouseInput() {
    DWORD prevMode;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS |
                               (prevMode & ~ENABLE_QUICK_EDIT_MODE));
}

void Console::setConsoleTitle() { SetConsoleTitleA("Pikachu++"); }

void Console::playSFX(int sound) {
    if (!soundEnabled) {
        return;
    }

    switch (sound) {
    case SFX_CORRECT:
        PlaySoundA("assets\\sfx\\correct.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;

    case SFX_WRONG:
        PlaySoundA("assets\\sfx\\wrong.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;

    case SFX_SELECT:
        PlaySoundA("assets\\sfx\\select.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;

    case SFX_WIN:
        PlaySoundA("assets\\sfx\\win.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;

    case SFX_START_GAME:
        PlaySoundA("assets\\sfx\\game_start.wav", NULL,
                   SND_FILENAME | SND_ASYNC);
        break;

    default:
        break;
    }
}

bool Console::isSoundEnabled() { return soundEnabled; }

void Console::setSoundEnabled(bool enabled) { soundEnabled = enabled; }

void Console::loadSettings() {
    ifstream fin("settings.txt");
    if (fin.is_open()) {
        bool darkMode;
        fin >> darkMode >> soundEnabled;
        fin.close();
        Colors::setDarkMode(darkMode);
    }
    Colors::setColors();
}

void Console::saveSettings() {
    ofstream fout("settings.txt");
    if (fout.is_open()) {
        fout << Colors::getIsDarkMode() << " " << soundEnabled;
        fout.close();
    }
}