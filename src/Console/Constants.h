#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window and console size
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define CONSOLE_WIDTH 172
#define CONSOLE_HEIGHT 42

// Sound effects
#define SFX_CORRECT 1
#define SFX_WRONG 2
#define SFX_SELECT 3
#define SFX_WIN 4
#define SFX_START_GAME 5

// Keys
const char K_BACKSPACE = 8;
const char K_ESC = 27;
const char K_ENTER = 13;
const char K_W = 'W';
const char K_w = 'w';
const char K_A = 'A';
const char K_a = 'a';
const char K_S = 'S';
const char K_s = 's';
const char K_D = 'D';
const char K_d = 'd';
const char K_H = 'H';
const char K_h = 'h';
const char K_R = 'R';
const char K_r = 'r';

// Background colors
const char *const BG_BLACK = "\33[0m";
const char *const BG_WHITE = "\33[107m";
const char *const BG_RED = "\33[41m";
const char *const BG_YELLOW = "\33[43m";
const char *const BG_ORANGE = "\33[48;5;208m";
const char *const BG_GREEN = "\33[42m";
const char *const BG_CYAN = "\33[46m";
const char *const BG_PURPLE = "\33[48;5;93m";
const char *const BG_PINK = "\33[48;5;199m";

// Text colors
const char *const TEXT_RED = "\33[31m";
const char *const TEXT_GREEN = "\33[32m";
const char *const TEXT_BLUE = "\33[34m";
const char *const TEXT_LIGHT_BLUE = "\33[38;5;33m";
const char *const TEXT_YELLOW = "\33[33m";
const char *const TEXT_DARK_RED = "\33[38;5;88m";
const char *const TEXT_ORANGE = "\33[38;5;208m";
const char *const TEXT_PURPLE = "\33[38;5;93m";
const char *const TEXT_MAGENTA = "\33[95m";
const char *const TEXT_WHITE = "\33[97m";
const char *const TEXT_BLACK = "\33[30m";
const char *const TEXT_PINK = "\33[38;5;199m";
const char *const TEXT_DARK_GRAY = "\33[38;5;8m";
const char *const TEXT_LIGHT_GRAY = "\33[38;5;7m";

// Box drawing characters - single
const char HORIZONTAL_EDGE = 196;   // ─
const char VERTICAL_EDGE = 179;     // │
const char LEFT_DOWN_CORNER = 191;  // ┐
const char RIGHT_UP_CORNER = 192;   // └
const char LEFT_UP_CORNER = 217;    // ┘
const char RIGHT_DOWN_CORNER = 218; // ┌

// Box drawing characters - double
const char D_HORIZONTAL_EDGE = 205;   // ═
const char D_VERTICAL_EDGE = 186;     // ║
const char D_LEFT_DOWN_CORNER = 187;  // ╗
const char D_RIGHT_UP_CORNER = 200;   // ╚
const char D_LEFT_UP_CORNER = 188;    // ╝
const char D_RIGHT_DOWN_CORNER = 201; // ╔

#endif