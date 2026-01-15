#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

#include "../Board/Board.h"
#include "../Board/Coordinate.h"
#include "../BoardRenderer/BoardRenderer.h"
#include "../Console/Colors.h"
#include "../Console/Console.h"
#include "../Console/Input.h"
#include "../Console/Renderer.h"
#include "Result.h"

using namespace std;

#define CORRECT_BONUS 50
#define WRONG_PENALTY -20
#define HINT_PENALTY -100
#define MAX_HINT 3

class Game {
private:
    Board *game_board;
    BoardRenderer *board_render;
    int board_height;
    int board_width;

    int score;
    Time play_time;
    string name;

    bool hint_used;
    bool shuffled;
    int hint_remaining;

    // Display the game stats
    void displayGameInfo();
    // Move the cursor displayed on screen
    void moveCursor(Coordinate &cur, Input inp);
    // Match two cells at position cur1 and cur2
    bool matchCell(Coordinate cur1, Coordinate cur2);
    // Change the displayed number of hints left on screen
    void updateRemainingHint();
    // Update the score displayed on screen
    void updateScore(int bonus_score);
    // Taking the name of the player
    void inputName(int x, int y);
    // Moving to the aftermath after completing a game
    void gameResult();

public:
    Game(int difficulty);
    ~Game();

    // Initializing a new game
    void initGame();
    // The main game loop
    void gameLoop();
};

#endif
