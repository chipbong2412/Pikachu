#ifndef INPUT_H
#define INPUT_H

#include <string>

using namespace std;

enum class Input {
    INVALID = -2,
    ESCAPE = -1,
    ENTER = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,
    RIGHT = 4,
    HINT = 5,
    SHUFFLE = 6
};

class InputHandler {
public:
    // Get user input and return corresponding Input enum
    static Input getInput();
};

#endif