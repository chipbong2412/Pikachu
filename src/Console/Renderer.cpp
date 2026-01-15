#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef byte
#endif

#include "Constants.h"
#include "Renderer.h"

void Renderer::goTo(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hStdout, Position);
}

void Renderer::changeTextColor(const string &bgColor, const string &textColor) {
    cout << bgColor << textColor;
}

void Renderer::drawBox(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        goTo(x, y + i);
        if (i == 0) {
            cout << D_RIGHT_DOWN_CORNER;
            cout << string(width - 2, D_HORIZONTAL_EDGE);
            cout << D_LEFT_DOWN_CORNER;
        } else if (i == height - 1) {
            cout << D_RIGHT_UP_CORNER;
            cout << string(width - 2, D_HORIZONTAL_EDGE);
            cout << D_LEFT_UP_CORNER;
        } else {
            cout << D_VERTICAL_EDGE;
            cout << string(width - 2, ' ');
            cout << D_VERTICAL_EDGE;
        }
    }
}

char Renderer::getCharAtPosition(short x, short y) {
    char c;
    COORD xy = {0, 0};
    CHAR_INFO ci;
    SMALL_RECT rect = {x, y, x, y};
    if (ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, {1, 1}, xy,
                          &rect)) {
        c = ci.Char.AsciiChar;
        return c;
    }
    return ' ';
}

void Renderer::setCursorAppearance(bool show) {
    if (show)
        cout << "\33[?25h"; // show cursor
    else
        cout << "\33[?25l"; // hide cursor
}